
time samtools view HG00123.cram -T /data/cb/inumanag/aldy/cram-genome.fa \
	| awk 'length($10)==76 {print $10}' \
	| shuf --random-source <(openssl enc -aes-256-ctr -pass pass:15101 -nosalt </dev/zero 2>/dev/null) \
	| head -n 100000000 \
	> HG00123_shuf.txt