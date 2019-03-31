// Old 16-mer experiment (C++)
// - Sums up the output of "process" function (here just returns k-mer length) 
//   on each 16-mers (step 2) in the file and outputs sum 
// and total number of processed k-mers

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int process(const string &kmer) {
   return kmer.size();
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long total = 0, total2 = 0;
   while (getline(fin, s)) {
      int i = 0;
      int k = 16;
      int step = 2;
      while (i + k < s.size()) {
         string sk = s.substr(i, k);
         total += process(sk);
         total2++;
         i += step;
      }
   }
   cout << total << ' ' << total2 << endl;

   return 0;
}
