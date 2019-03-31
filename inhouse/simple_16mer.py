# Old 16-mer experiment (Python)
# - Sums up the output of "process" function (here just returns k-mer length) 
#   on each 16-mers (step 2) in the file and outputs sum 
#   and total number of processed k-mers

import sys

def process(k):
   return len(k)

def ksplit(s, k, step):
   i = 0
   while i + k < len(s):
      yield s[i:i + k]
      i += step

f = open(sys.argv[1], 'r')
total, t2 = 0, 0
k, step = 16, 2
for l in f:
   for s in ksplit(l.strip(), k, step):
      total += process(s)
      t2 += 1
print total, t2
