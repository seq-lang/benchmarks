#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <seqan/sequence.h>
#include <seqan/basic.h>
#include <seqan/stream.h>
#include <seqan/file.h>
#include <seqan/modifier.h>
using namespace seqan;

typedef Infix<String<Dna5>>::Type SubStr;

int process(const SubStr &kmer) {
   return length(kmer);
}

int sym(const SubStr &q) {
   int len = length(q);
   auto p = prefix(q, len/2);
   auto s = suffix(q, len/2);
   ModifiedString<ModifiedString<Infix<String<Dna5>>::Type, ModComplementDna5>, ModReverse> v(s);
   return p == v;
}

int sym2(const SubStr &q) {
   ModifiedString<ModifiedString<Infix<String<Dna5>>::Type, ModComplementDna5>, ModReverse> v(q);
   return q == v;
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long total = 0, total2 = 0, total3 = 0;
   while (getline(fin, s)) {
      String<Dna5> d(s);
      int i = 0;
      int k = 16;
      int step = 1;
      while (i + k <= s.size()) {
         SubStr inf = infix(d, i, i + k);
         total += process(inf);
         total2++;
         total3 += sym(inf);
         i += step;
      }
   }
   cout << total << ' ' << total2 << ' ' << total3 << endl;
   return 0;
}
