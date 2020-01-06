import sys
import Bio.Seq

def rc_copy(s):
   rc = s.reverse_complement()
   print rc
   return len(rc)

f = open(sys.argv[1], 'r')
total = 0
for l in f:
   total += rc_copy(Bio.Seq.Seq(l.strip()))
print total
