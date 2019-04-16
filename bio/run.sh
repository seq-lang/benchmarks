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

for FQ in "HG00123_5mil.fq"
do 
	for S in 6 7 ; do 
		echo "=== === === === === === === $S === === === === === === ==="
		${SEQ}/build_tapir/seq-par-compile sga_$S.seq build "-Lbuild -lsga"
		for T in 1 2 3 4 ; do 
			echo "=> Running Seq/$T with $FQ ..."
			export OMP_NUM_THREADS=$T
			for k in 1 2 3 ; do 
				/usr/bin/time -f'[time: %e s | mem: %M kb]' \
			  taskset -c 20,21,22,23 \
			  ${SEQ}/build_tapir/seq-par-run build/sga_$S.seq data/wgsim-sga.bwt data/$FQ
			done
		done
  done
done
exit 0

# S="snap"
# for FQ in "HG00123_shuf.fq" # "ERR194146_5mil.fq" "snap-ariya.fq" "NA12878-10x_5mil.fq" "HG00123_shuf.fq"
# do
# 	echo "=== === === === === === === $S === === === === === === ==="
# 	ls -lah data/$FQ 
# 	echo "==> Compiling..."
# 	echo "=> Compiling $S.cc..."
# 	g++ -O3 -march=native -o build/$S.cc $S.cc -Lbuild -lsnap -std=c++11
# 	clang++ -O3 -march=native -o build/$S.cl $S.cc -Lbuild -lsnap -std=c++11
# 	seq-compile $S.seq build "-Lbuild -lsnap"

# 	echo "==> Running..."
# 	echo "=> Running C++/g++ with $FQ ..."
# 	#hf 5 "build/$S.cc  data/snap_hg19_index data/$FQ    > out/${FQ}-snap.cc"

# 	echo "=> Running C++/clang++ with $FQ ..."
# 	#hf 5 "build/$S.cl  data/snap_hg19_index data/$FQ    > out/${FQ}-snap.cl"

# 	echo "=> Running Seq with $FQ ..."
# 	hf 5 "build/$S.seq data/snap_hg19_index data/$FQ n > out/${FQ}-snap_n.seq"

# 	echo "=> Running Seq/P with $FQ ..."
# 	hf 5 "build/$S.seq data/snap_hg19_index data/$FQ y > out/${FQ}-snap_y.seq"
# done

# exit 0

S="sga"
for FQ in "HG00123_5mil.fq" # "ERR194146_5mil.fq" "sga-ariya.fq" "NA12878-10x_5mil.fq" 
do
	echo "=== === === === === === === $S === === === === === === ==="
	ls -lah data/$FQ 
	echo "==> Compiling..."
	echo "=> Compiling $S.cc..."
	make -f Makefile.sga
	make -f Makefile.sga clang
	seq-compile $S.seq build "-Lbuild -lsga"

	echo "==> Running..."
	echo "=> Running C++/g++ with $FQ ..."
	#hf 5 "build/$S.cc  data/wgsim-sga.bwt data/$FQ    > out/${FQ}-sga.cc"

	echo "=> Running C++/clang++ with $FQ ..."
	#hf 5 "build/$S.cl  data/wgsim-sga.bwt data/$FQ    > out/${FQ}-sga.cl"

	echo "=> Running Seq with $FQ ..."
	hf 2 "build/$S.seq data/wgsim-sga.bwt data/$FQ n > out/${FQ}-sga_n.seq"

	echo "=> Running Seq/P with $FQ ..."
	hf 2 "build/$S.seq data/wgsim-sga.bwt data/$FQ y > out/${FQ}-sga_y.seq"
done