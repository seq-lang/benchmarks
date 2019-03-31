#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>
#include <cassert>

#include <sys/time.h>

int seq_time()
{
	timeval ts;
	gettimeofday(&ts, nullptr);
	auto time_ms = (int)((ts.tv_sec * 1000000 + ts.tv_usec) / 1000);
	return time_ms;
}

struct BWTInterval {
	BWTInterval() : lower(0), upper(0) {}
	BWTInterval(int64_t l, int64_t u) : lower(l), upper(u) {}

	inline bool isValid() const { return lower <= upper; }
	inline int64_t size() const { return upper - lower + 1; }

	int64_t lower;
	int64_t upper;
};

extern "C" void *sga_idx_new(const char *path);
extern "C" void sga_init_interval(void *bwt, BWTInterval *interval, char b);
extern "C" void sga_update_interval(void *bwt, BWTInterval *interval, char b);

using namespace std;

static inline bool hasN(char *kmer, unsigned len)
{
	for (unsigned i = 0; i < len; i++) {
		if (kmer[i] == 'N')
			return true;
	}
	return false;
}

static BWTInterval find_interval(void *pBWT, const char *w, int len)
{
	int j = len - 1;
	char curr = w[j];
	BWTInterval interval;
	sga_init_interval(pBWT, &interval, curr);
	--j;

	for(;j >= 0; --j)
	{
		curr = w[j];
		sga_update_interval(pBWT, &interval, curr);
		if(!interval.isValid())
			return interval;
	}

	return interval;
}

int main(int argc, char *argv[])
{
	assert(argc == 3);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t = seq_time();
	void *idx = sga_idx_new(argv[1]);
	cerr<<"index loaded in " << (seq_time()-t)/1000.0 << endl;

	const unsigned k = 20;
	const unsigned step = 1;
	int good = 0, bad = 0;

	ifstream fin(argv[2]);
	string read;
	long line = -1;

	while (getline(fin, read)) {
		line++;
		if (line % 4 != 1)
			continue;

		char *buf = (char *)read.c_str();
		unsigned len = read.size();
		unsigned offset = 0;

		for (unsigned i = 0; i + k <= len; i += step) {
			if (hasN(&buf[i], k))
				continue;
			//printf("%s\n", buf);
			//continue;

			BWTInterval interval = find_interval(idx, &buf[i], k);
			(interval.isValid() ? good : bad)++;
		}
	}

	cout << good << " " << bad << endl;
}
