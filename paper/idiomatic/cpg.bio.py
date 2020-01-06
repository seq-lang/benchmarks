import sys
import Bio.Seq

def cpg(s):
   for c in s:
      i = 1 if c == 'C' else (2 if c == 'G' else 0)
      if i == 0: break
      yield i

m, M = 99999, 0
def cpg_count(s):
   mm, MM = 99999, 0
   i = 0
   count = 0
   while i < len(s):
      cc, l = 0, 0
      for j in cpg(s[i:]):
         cc |= j
         l += 1
      if cc == 3:
         count += 1
         mm = min(mm, l)
         MM = max(MM, l)
      i += l + 1
   global m, M
   m = min(mm, m)
   M = max(MM, M)
   return count

f = open(sys.argv[1], 'r')
cnt = 0
for l in f:
   cnt += cpg_count(Bio.Seq.Seq(l.strip()))
print cnt, m, M
