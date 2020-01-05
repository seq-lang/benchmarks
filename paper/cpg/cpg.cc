// 786
// benchmarks:
// - count number of CpG islands (e.g. all CG-only subseqs)

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

char is_cpg(char s) {
   if (s == 'C') return 1; 
   if (s == 'G') return 2;
   return 0;
}

int m=99999, M=0;
long long cpg_count(string s) {
   long long count = 0;
   int i = 0;
   char c;
   while (i < s.size()) {
      char cc = 0; int l = 0;
      while (i < s.size() && (c = is_cpg(s[i]))) {
         cc |= c;
         i++; l++;
      }
      if (cc == 3) {
         count ++;
         m=min(m, l);
         M=max(M, l);
      }
      i++;
   }
   return count;
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
	 cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long res = 0;
   while (getline(fin, s)) {
      res += cpg_count(s);
   }
   cout << res << ' ' << m << ' ' << M << endl;

   return 0;
}
