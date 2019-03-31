# 786
# benchmarks:
# - reverse complementing 10g FASTA
# - printing all 16-mers from 10g FASTA
# - count number of CpG islands (e.g. all CG-only subseqs)

import sys

def is_cpg(s):
   return 1 if s == 'C' else (2 if s == 'G' else 0)

def cpg(s):
   for c in s:
      i = is_cpg(c)
      if i == 0: break
      yield i

m, M = 99999, 0
def cpg_count(s):
   global m, M
   i = 0
   count = 0
   while i < len(s):
      cc, l = 0, 0
      for j in cpg(s[i:]):
         cc |= j
         l += 1
      if cc == 3:
         count += 1
         m = min(m, l)
         M = max(M, l)
      i += l + 1
   return count

f = open(sys.argv[1], 'r')
cnt = 0
for l in f:
   cnt += cpg_count(l)
print cnt, m, M
