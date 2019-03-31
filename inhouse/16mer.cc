// 786
// benchmarks:
// - reverse complementing 10g FASTA
// - printing all 16-mers from 10g FASTA
// - count number of CpG islands (e.g. all CG-only subseqs)

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

char revcomp(char c) {
   return (c == 'T' ? 'A' :
          (c == 'G' ? 'C' :
          (c == 'C' ? 'G' :
          (c == 'A' ? 'T' : c))));
}

int process(const string &kmer) {
   return kmer.size();
}

int sym(const string &s, int k) {
   for (int j = 0; j < k/2; j++)
      if (s[j] != revcomp(s[k-j-1])) {
         return 0;
      }
   return 1;
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long total = 0, total2 = 0, total3 = 0;
   while (getline(fin, s)) {
      int i = 0;
      int k = 16;
      int step = 1;
      while (i + k <= s.size()) {
         string sk = s.substr(i, k);
         total += process(sk);
         total2++;
         total3 += sym(sk, k);
         i += step;
      }
   }
   cout << total << ' ' << total2 << ' ' << total3 << endl;

   return 0;
}
