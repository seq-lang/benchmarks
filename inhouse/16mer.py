# 786
# benchmarks:
# - reverse complementing 10g FASTA
# - printing all 16-mers from 10g FASTA
# - count number of CpG islands (e.g. all CG-only subseqs)

import sys

def revcomp(c):
   return ('A' if c == 'T' else \
          ('C' if c == 'G' else \
          ('G' if c == 'C' else \
          ('T' if c == 'A' else c))))

def process(k):
   return len(k)

def ksplit(s, k, step):
   i = 0
   while i + k <= len(s):
      yield s[i:i + k]
      i += step

def sym(s, k):
   return 1 if all(s[i] == revcomp(s[-i-1]) for i in range(k//2)) else 0

f = open(sys.argv[1], 'r')
total, t2, t3 = 0, 0, 0
k = 16
for l in f:
   for s in ksplit(l.strip(), k, 1):
      total += process(s)
      t2 += 1
      t3 += sym(s, k)
print total, t2, t3
