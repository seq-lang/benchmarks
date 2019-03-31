#!/bin/bash
# Use Conda Python

export SEQ=/scratch2/ibrahim/seq
export PATH="${SEQ}/build/miniconda/bin:${SEQ}/build:$PATH"
export SEQ_PATH="${SEQ}/stdlib"
export LD_LIBRARY_PATH="${SEQ}/build:${LD_LIBRARY_PATH}"

hf () {
	hyperfine -r $1 --show-output \
		 "/usr/bin/time -f'[time: %e s | mem: %M kb]' \
		  taskset -c 20 \
		  $2"
}

run () {
	S=$1
	echo "=== === === === === === === $S === === === === === === ==="
	echo "==> Compiling..."
	echo "=> Compiling $S.cc..."
	g++ -O3 -march=native -o build/$S.cc $S.cc -std=c++11 
	echo "=> Compiling $S.cl..."
	clang++ -O3 -march=native -o build/$S.cl $S.cc -std=c++11 
	echo "=> Compiling $S.seq..."
	seq-compile $S.seq build
	echo "=> Compiling $S.nuitka..."
	nuitka --standalone --python-flag=noasserts,no_warnings --lto \
		--output-dir="build/$S.nuitka" --remove-output $S.py

	echo "==> Running..."
	echo "=> Running C++/g++ with $2 ..."
	hf 5 "build/$S.cc $2 > out/$S.cc" 

	echo "=> Running C++/clang++ with $2 ..."
	hf 5 "build/$S.cl $2 > out/$S.cl" 

	echo "=> Running Seq with $2 ..."
	hf 5 "build/$S.seq $2 > out/$S.seq" 

	echo "=> Running Julia with $2 ..."
	hf 5 "julia --check-bounds=no -O3 $S.jl $2 > out/$S.jl" 

	echo "=> Running Python with $2 ..."
	hf 3 "python $S.py $2 > out/$S.py" 

	echo "=> Running Nuitka with $2 ..."
	hf 3 "build/$S.nuitka/$S.dist/$S $2 > out/$S.nuitka" 
}

run "fasta" "25000000"
run "revcomp" "< data/fasta25mil.txt" 
run "knucleotide" "< data/fasta25mil.txt"
