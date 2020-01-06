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

int m=99999, M=0;
long long cpg_count(const String<Dna> &s) {
   long long count = 0;
   int i = 0;
   char c;
   int mm=99999, MM=0; 
   while (i < length(s)) {
      char cc = 0; int l = 0;
      while (i < length(s) && (ordValue(s[i]) == 1 || ordValue(s[i]) == 2)) {
         cc |= ordValue(s[i]);
         i++; l++;
      }
      if (cc == 3) {
         count++;
         mm=min(mm, l); MM=max(MM, l);
      }
      i++;
   }
   m = min(m, mm); M = max(M, MM);
   return count;
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
	 cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long res = 0;
   while (getline(fin, s)) {
      res += cpg_count(String<Dna>(s));
   }
   cout << res << ' ' << m << ' ' << M << endl;

   return 0;
}
