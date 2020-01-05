#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<char> maketrans(string inp, string out) {
   vector<char> a;
   for (int i = 0; i < 128; i++) a.push_back(i);
   for (int i = 0; i < inp.size(); i++) 
      a[inp[i]] = out[i];
   return a;
}

void process(const vector<string> &l, const vector<char> &trans) {
   if (!l.size()) return;
   int j = 0, width = 60;
   for (int i = l.size() - 1; i >= 0; i--) 
      for (int c = l[i].size() - 1; c >= 0; c--) {
         putchar(trans[l[i][c]]);
         j++;
         if (j == width) {
            putchar('\n');
            j = 0;
         }
      }
   if (j) putchar('\n');
}

int main(void) {
   vector<char> trans = maketrans(
      "ACBDGHKMNSRUTWVYacbdghkmnsrutwvy",
      "TGVHCDMKNSYAAWBRTGVHCDMKNSYAAWBR");
   vector<string> l;
   string line;
   while (getline(cin, line)) {
      if (line[0] == '>') {
         process(l, trans);
         printf("%s\n", line.c_str());
         l.clear();
      } else l.push_back(line);
   }
   process(l, trans);
   return 0;
}
