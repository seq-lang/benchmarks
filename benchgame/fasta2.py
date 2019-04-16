import sys, bisect, time

alu = 'GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGGGAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGACCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAAAATACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCAGCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAACCCGGGAGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCCAGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA'
iub = list(zip('acgtBDHKMNRSVWY', [0.27, 0.12, 0.12, 0.27] + [0.02]*11))

homosapiens = [
    ('a', 0.3029549426680),
    ('c', 0.1979883004921),
    ('g', 0.1975473066391),
    ('t', 0.3015094502008)
]

def random_generator(ia, ic, im):
    seed = 42
    imf = float(im)
    while 1:
        seed = (seed * ia + ic) % im
        yield seed / imf

def make_cumulative(table):
    P = []
    C = []
    prob = 0.
    for char, p in table:
        prob += p
        P += [prob]
        C += [char]
    return (P, C)

def repeat_fasta(src, n):
    width = 60
    r = len(src)
    s = src + src + src[:n % r]
    for i in range(0, n // width):
        j = i * width % r
        print s[j:j + width]
    if n % width: print s[- (n % width):]

def random_fasta(table, n, rand):
    width = 60
    probs, chars = make_cumulative(table)
    s = ''.join([chars[bisect.bisect(probs, next(rand))] for i in range(n)])
    for i in range(0, n, width):
        print s[i:i + width]

n = int(sys.argv[1]) 

rand = random_generator(3877, 29573, 139968)

print '>ONE Homo sapiens alu'
repeat_fasta(alu, n*2)

print '>TWO IUB ambiguity codes'
random_fasta(iub, n*3, rand)

print '>THREE Homo sapiens frequency'
random_fasta(homosapiens, n*5, rand)
