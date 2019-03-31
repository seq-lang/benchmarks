# Old CpG experiment (Python)
# - Counts the number of non-overlapping [CG]+ regions 

import sys

def is_cpg(s):
   return s == 'C' or s == 'G' 

def cpg_count(s):
   i = 0
   total = 0
   while i < len(s):
      if is_cpg(s[i]):
         j = i + 1
         while j < len(s) and is_cpg(s[j]):
            j += 1
         total += 1
         i = j + 1
      else: i += 1
   return total

f = open(sys.argv[1], 'r')
cnt = 0
for l in f:
   cnt += cpg_count(l.strip())
print cnt
