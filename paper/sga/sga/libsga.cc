#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>
#include <cassert>

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
extern "C" void sga_update_interval_prefetch(void *bwt, int64_t lower, int64_t upper, char b);

int main(int argc, char *argv[])
{
	sga_idx_new(argv[0]);
}

