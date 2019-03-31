// Old CpG experiment (C++)
// - Counts the number of non-overlapping [CG]+ regions 

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool is_cpg(char s) {
   return (s == 'C' || s == 'G');
}

long long cpg_count(const string &s) {
   long long count = 0;
   int i = 0;
   while (i < s.size()) {
      if (is_cpg(s[i])) {
         int j = i + 1;
         while (j < s.size() && is_cpg(s[j])) {
            j++;
         }
         count++;
         i = j + 1;
      } else i++;
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
   cout << res << endl;

   return 0;
}
