#!/bin/bash
# Use Conda Python


export SEQ=/scratch2/ibrahim/seq
export PATH="${SEQ}/build/miniconda/bin:${SEQ}/build:$PATH"
export SEQ_PATH="${SEQ}/stdlib"
export LD_LIBRARY_PATH="${SEQ}/build:build:${LD_LIBRARY_PATH}"

hf () {
	hyperfine -r $1 --show-output \
		 "/usr/bin/time -f'[time: %e s | mem: %M kb]' \
		  taskset -c 20 \
		  $2"
}

# S="snap"
# FQ="data/NA12878-10x.fq"
# FQ="data/snap-ariya.fq"
# # FQ="../inhouse/data/HG00123_shuf.txt"
# ls -lah $FQ
# # For SNAP: /scratch2/arshajii/seq/data/test_wgsim.1.fq
# echo "=== === === === === === === $S === === === === === === ==="
# echo "==> Compiling..."
# echo "=> Compiling $S.cc..."
# g++ -O3 -march=native -o build/$S.cc $S.cc -Lbuild -lsnap -std=c++11 
# seq-compile $S.seq build "-Lbuild -lsnap"

# echo "==> Running..."
# echo "=> Running C++/g++ with $2 ..."
# hf "build/$S.cc  data/snap_hg19_index $FQ > out/snap_1.cc"

# echo "=> Running Seq with $2 ..."
# hf "build/$S.seq data/snap_hg19_index $FQ n > out/snap_n.seq"

# echo "=> Running Seq/P with $2 ..."
# hf "build/$S.seq data/snap_hg19_index $FQ y > out/snap_y.seq"

S="sga"
for FQ in "HG00123_5mil.fq" "ERR194146_5mil.fq" "sga-ariya.fq" "NA12878-10x_5mil.fq" 
do
	echo "=== === === === === === === $S === === === === === === ==="
	ls -lah data/$FQ 
	echo "==> Compiling..."
	echo "=> Compiling $S.cc..."
	make -f Makefile.sga
	seq-compile $S.seq build "-Lbuild -lsga"

	echo "==> Running..."
	echo "=> Running C++/g++ with $FQ ..."
	#hf 5 "build/$S.cc  data/wgsim-sga.bwt data/$FQ    > out/${FQ}-sga.cc"

	echo "=> Running Seq with $FQ ..."
	hf 5 "build/$S.seq data/wgsim-sga.bwt data/$FQ n > out/${FQ}-sga_n.seq"

	echo "=> Running Seq/P with $FQ ..."
	hf 5 "build/$S.seq data/wgsim-sga.bwt data/$FQ y > out/${FQ}-sga_y.seq"
done