// g++ -std=c++11 -O3 -march=native -o test -L/scratch2/arshajii/snap/ -lsnap test.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <sys/time.h>

using namespace std;

int seq_time()
{
	timeval ts;
	gettimeofday(&ts, nullptr);
	auto time_ms = (int)((ts.tv_sec * 1000000 + ts.tv_usec) / 1000);
	return time_ms;
}

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

void update(unordered_map<unsigned,unsigned> &counts, unsigned pos, unsigned &max_pos, unsigned &max_count)
{
	unsigned count = counts[pos] + 1;
	counts[pos] = count;
	if (count > max_count) {
		max_pos = pos;
		max_count = count;
	}
}

void process(void *idx, char **argv)
{
	const unsigned k = 20;
	const unsigned step = k;

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
		unsigned offset = 0;

		for (unsigned i = 0; i + k <= len; i += step) {
			if (hasN(&buf[i], k))
				continue;

			snap_index_lookup(idx, &buf[i], &n_hits, &hit_p, &n_hits_rc, &hit_rc_p);

			if (n_hits + n_hits_rc <= 100) {
				for (int64_t i = 0; i < n_hits; i++) {
					unsigned pos = hit_p[i] - offset;
					update(counts, pos, max_pos, max_count);
				}

				for (int64_t i = 0; i < n_hits_rc; i++) {
					unsigned pos = hit_rc_p[i] - offset;
					update(counts, pos, max_pos, max_count);
				}
			}

			offset += step;
		}

		cout << read << " " << max_pos << endl;
	}
}

void processn(void *idx, char **argv)
{
	const unsigned k = 20;
	const unsigned step = k;

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
		unsigned offset = 0;

		for (unsigned i = 0; i + k <= len; i += step) {
			if (hasN(&buf[i], k))
				continue;

			snap_index_lookup(idx, &buf[i], &n_hits, &hit_p, &n_hits_rc, &hit_rc_p);

			{
				for (int64_t i = 0; i < n_hits; i++) {
					unsigned pos = hit_p[i] - offset;
					update(counts, pos, max_pos, max_count);
				}

				for (int64_t i = 0; i < n_hits_rc; i++) {
					unsigned pos = hit_rc_p[i] - offset;
					update(counts, pos, max_pos, max_count);
				}
			}

			offset += step;
		}

		cout << read << " " << max_pos << endl;
	}
}


int main(int argc, char *argv[])
{
	assert(argc == 4);

	int t = seq_time();
	void *idx = snap_index_from_dir(argv[1]);
	cerr<<"index loading:"<<(seq_time()-t)/1000.0<<endl;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	if (string(argv[3])=="1")
		process(idx, argv);
	else if (string(argv[3])=="2")
		processn(idx, argv);
	else cerr << "wrong mode" << endl;
	return 0;

}
