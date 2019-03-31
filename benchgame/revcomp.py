import sys

def maketrans(inp, out):
   a = [chr(i) for i in range(128)]
   for i, c in enumerate(inp):
      a[ord(c)] = out[i]
   return a
trans = maketrans(
   'ACBDGHKMNSRUTWVYacbdghkmnsrutwvy',
   'TGVHCDMKNSYAAWBRTGVHCDMKNSYAAWBR')

def process(l, trans):
   if len(l) == 0:
      return
   j, width = 0, 60
   for i in range(len(l) - 1, -1, -1):
      for c in range(len(l[i]) - 1, -1, -1):
         sys.stdout.write(trans[ord(l[i][c])])
         j += 1
         if j == width:
            sys.stdout.write("\n")
            j = 0
   if j != 0:
      sys.stdout.write("\n")

l = []
for line in sys.stdin:
   if line[0] == '>':
      process(l, trans)
      print line.strip()
      l = []
   else:
      l.append(line.strip())
process(l, trans)
