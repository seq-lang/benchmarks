// g++ -std=c++11 -O3 -march=native -o test -L/scratch2/arshajii/snap/ -lsnap test.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>
#include <cassert>

using namespace std;

extern "C" void *snap_index_from_dir(char *dir);
extern "C" void snap_index_lookup(void *idx, char *bases, int64_t *nHits, const unsigned **hits, int64_t *nRCHits, const unsigned **rcHits);

static bool hasN(char *kmer, unsigned len)
{
	for (unsigned i = 0; i < len; i++) {
		if (kmer[i] == 'N')
			return true;
	}
	return false;
}

int good = 0;
int bad = 0;

int main(int argc, char *argv[])
{
	assert(argc == 3);

	void *idx = snap_index_from_dir(argv[1]);
	const unsigned k = 20;
	const unsigned step = 10;

	unsigned hit = 0;
	unsigned hit_rc = 0;
	int64_t n_hits = 0;
	int64_t n_hits_rc = 0;
	const unsigned *hit_p = &hit;
	const unsigned *hit_rc_p = &hit_rc;

	ifstream fin(argv[2]);
	string read;
	long line = -1;

	while (getline(fin, read)) {
		line++;
		if (line % 4 != 1)
			continue;

		unordered_map<unsigned,unsigned> counts;
		unsigned max_pos = 0, max_count = 0;
		char *buf = (char *)read.c_str();
		unsigned len = read.size();

		for (unsigned i = 0; i + k <= len; i += step) {
			if (hasN(&buf[i], k))
				continue;

			snap_index_lookup(idx, &buf[i], &n_hits, &hit_p, &n_hits_rc, &hit_rc_p);
			++((n_hits > 0 || n_hits_rc > 0) ? good : bad);
		}
	}

	cout << good << " " << bad << endl;
}
