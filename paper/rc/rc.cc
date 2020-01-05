// 786
// benchmarks:
// - reverse complementing 10g FASTA

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

int rc_copy(string s) {
   string x = s;
   for (int i = 0; i < x.size(); i++)
      x[i] = revcomp(s[s.size() - i - 1]);
   cout << x << endl;
   return x.size();
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
	 cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long total = 0;
   while (getline(fin, s)) {
      total += rc_copy(s);
   }
   cout << total << endl;

   return 0;
}
