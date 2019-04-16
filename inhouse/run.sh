#!/bin/bash
# Use Conda Python
# set -x

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
	if [ -f "$S.id.seq" ] ; then 
		echo "=> Compiling $S.id.seq..."
		seq-compile $S.id.seq build
	fi
	if [ -f "$S.par.seq" ] ; then 
		echo "=> Compiling $S.par.seq..."
		${SEQ}/build_tapir/seq-par-compile $S.par.seq build
	fi
	echo "=> Compiling $S.nuitka..."
	#nuitka --standalone --python-flag=noasserts,no_warnings --lto \
	#		--output-dir="build/$S.nuitka" --remove-output $S.py
	echo "=> Compiling $S.shed..."
	/afs/csail.mit.edu/u/i/inumanag/.local/bin/shedskin -l -o ${S}2 
	make
	mv ${S}2 build/${S}.shed

	echo "==> Running..."
	echo "=> Running C++/g++ with $2 ..."
	#hf 5 "build/$S.cc $2 > out/$S.cc"

	echo "=> Running C++/clang++ with $2 ..."
	#hf 5 "build/$S.cl $2 > out/$S.cl"

	echo "=> Running Seq with $2 ..."
	#hf 5 "build/$S.seq $2 > out/$S.seq"

	if [ -f "$S.id.seq" ]; then 
		echo "=> Running Seq.ID with $2 ..."
		#hf 5 "build/$S.id.seq $2 > out/$S.id.seq"
	fi

	# if [ -f "$S.par.seq" ]; then 
	# 	for t in 1 2 3 4 ; do
	# 		echo "=> Running Seq.PAR with $2 ..."
	# 		export OMP_NUM_THREADS=$t
	# 		hf 5 "${SEQ}/build_tapir/seq-par-run build/$S.par.seq $2 > out/$S.par.seq"
	# 	done
	# fi

	echo "=> Running Julia with $2 ..."
	#hf 3 "julia --check-bounds=no -O3 $S.jl $2 > out/$S.jl"

	echo "=> Running Nuitka with $2 ..."
	#hf 3 "build/$S.nuitka/$S.dist/$S $2 > out/$S.nuitka"

	echo "=> Running Python with $2 ..."
	#hf 3 "python $S.py $2 > out/$S.py"

	echo "=> Running Shedskin with $2 ..."
	hf 3 "build/$S.shed $2 > out/$S.shed" 
}

run "rc" "data/HG00123_shuf.txt"
run "cpg" "data/HG00123_shuf.txt"
run "16mer" "data/HG00123_shuf.txt"
