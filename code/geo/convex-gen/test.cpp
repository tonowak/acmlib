#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#define rng rng_wrapper
#define rd rd_wrapper
#include "main.cpp"
#undef rng
#undef rd

void test() {
	const double PROC = 0.9;
	int N = rd(3, 1'000);
	int z = int(1e5);
	// cerr << N;
	auto loose = gen_convex_polygon(N, z);
	int n = ssize(loose);
	// cerr << ' ' << n;
	assert(n >= N * PROC);

	REP (i, n)
		assert(abs(loose[i].x()) <= z && abs(loose[i].y()) <= z);

	const int reps = 100;
	REP (rep, reps) {
		int mid = rd(0, n - 1);
		auto middle = loose[mid];
		REP (j, n)
			loose[j] -= middle;
		for (int j = (mid + 1) % n; (j + 1) % n != mid; j = (j + 1) % n)
			assert(dir(loose[j], loose[mid], loose[(j + 1) % n]) >= 0);
	}

	auto strict = gen_convex_polygon(N, z, true);
	n = ssize(strict);
	// cerr << ' ' << n << endl;
	assert(n >= N * PROC);

	REP (i, n)
		assert(abs(strict[i].x()) <= z && abs(strict[i].y()) <= z);

	REP (rep, reps) {
		int mid = rd(0, n - 1);
		auto middle = strict[mid];
		REP (j, n)
			strict[j] -= middle;
		for (int j = (mid + 1) % n; (j + 1) % n != mid; j = (j + 1) % n)
			assert(dir(strict[j], strict[mid], strict[(j + 1) % n]) > 0);
	}
}
