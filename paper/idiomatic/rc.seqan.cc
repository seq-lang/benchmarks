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

int rc_copy(const String<Dna5> &s) {
   auto x = s;
   reverseComplement(x);
   cout << x << endl;
   return length(x);
}

int main(int argc, char **argv) {
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);

   ifstream fin(argv[1]);
   string s;
   long long total = 0;
   while (getline(fin, s)) {
      total += rc_copy(String<Dna5>(s));
   }
   cout << total << endl;

   return 0;
}
