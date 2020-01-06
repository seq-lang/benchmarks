import sys
import Bio.Seq

def process(k):
   return len(k)

def ksplit(s, k, step):
   i = 0
   while i + k <= len(s):
      yield s[i:i + k]
      i += step

def sym(q):
   k = len(q)
   p = q[:k//2]
   s = q[k//2:].reverse_complement()
   return p == s

f = open(sys.argv[1], 'r')
total, t2, t3 = 0, 0, 0
k = 16
for l in f:
   for s in ksplit(l.strip(), k, 1):
      s = Bio.Seq.Seq(s)
      total += process(s)
      t2 += 1
      t3 += sym(s)
print total, t2, t3
