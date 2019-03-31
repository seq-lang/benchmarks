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

def rc_copy(s):
   rc = ''.join(
      revcomp(s[len(s) - i - 1]) for i in range(len(s)))
   print rc
   return len(rc)

f = open(sys.argv[1], 'r')
total = 0
for l in f:
   total += rc_copy(l.strip())
print total
