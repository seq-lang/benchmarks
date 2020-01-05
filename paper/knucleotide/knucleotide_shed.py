import sys, time

def hashcnt(s, k):
  d = {}
  for i in range(0, len(s) - k + 1):
    q = s[i:i+k]
    d[q] = d.get(q, 0) + 1
  return d

def cnt(s, q):
  d = hashcnt(s, len(q))
  print str(d.get(q, 0)) + "\t" + q

def freq(s):
  d1 = hashcnt(s, 1)
  for k, v in sorted(d1.items(), key=lambda x: x[1], reverse=True):
    print ('%s %6.3f' % (k, (100.0 * v) / len(s)))
  print 

  d2 = hashcnt(s, 2)
  for k, v in sorted(d2.items(), key=lambda x: x[1], reverse=True):
    print ('%s %5.3f' % (k, (100.0 * v) / (len(s)-1)))
  print

def process(sq):
  freq(sq)
  cnt(sq, 'GGT')
  cnt(sq, 'GGTA')
  cnt(sq, 'GGTATT')
  cnt(sq, 'GGTATTTTAATT')
  cnt(sq, 'GGTATTTTAATTTATAGT')

for line in sys.stdin:
  if line[:6] == '>THREE':
    l = []
    for line in sys.stdin:
      if line[0] == '>': break
      l.append(line.strip())
    s = ''.join(l).upper()
    process(s)
    break
