#include <iostream>
#include <vector>
#include <string>
using namespace std;

double random_generator(int ia=3877, int ic=29573, int im=139968) {
    static int seed (42);
    double imf = im;
    while (true) {
        seed = (seed * ia + ic) % im;
        return seed / imf;
    }
}

pair<vector<double>, string> make_iub() {
    string c = "acgtBDHKMNRSVWY";
    vector<double> p = { 0.27, 0.12, 0.12, 0.27 };
    for (int i = 1; i < 4; i++)
        p[i] += p[i - 1];
    for (int i = 4; i < c.size(); i++) {
        p.push_back(p[i - 1] + 0.02);
    }
    return make_pair(p, c);
}

pair<vector<double>, string> make_human() {
    string c = "acgt";
    vector<double> p = { 0.3029549426680, 0.1979883004921, 0.1975473066391, 0.3015094502008 };
    for (int i = 1; i < 4; i++) {
        p[i] += p[i - 1];
    }
    return make_pair(p, c);
}

void repeat_fasta(int n) {
    string src = "GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGGGAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGACCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAAAATACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCAGCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAACCCGGGAGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCCAGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";
    int width = 60;
    int r = src.size();
    string s = src + src + src.substr(0, n % r);
    for (int j = 0; j < n / width; j++) {
        int i = j * width % r;
        printf("%s\n", s.substr(i, width).c_str());
    }
    if (n % width)
        printf("%s\n", s.substr(s.size() - n % width).c_str());
}

int bisect(const vector<double> &a, double x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = (lo+hi)/2;
        if (x < a[mid]) hi = mid;
        else lo = mid+1;
    }
    return lo;
}

void random_fasta(pair<vector<double>, string> table, int n) {
    int width = 60;
    vector<double> probs = table.first;
    string chars = table.second;
    for (int j = 0; j < n / width; j++) {
        for (int i = 0; i < width; i++)
            putchar(chars[bisect(probs, random_generator())]);
        putchar('\n');
    }
    if (n % width) {
        for (int i = 0; i < n % width; i++)
            putchar(chars[bisect(probs, random_generator())]);
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    printf(">ONE Homo sapiens alu\n");
    repeat_fasta(n*2);

    printf(">TWO IUB ambiguity codes\n");
    random_fasta(make_iub(), n*3);

    printf(">THREE Homo sapiens frequency\n");
    random_fasta(make_human(), n*5);

    return 0;
}


