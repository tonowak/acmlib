#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	LL mn = 1e3;
	LL mc = 1e9;
	LL n = rd(1, mn);
	LL c = rd(1, mc);
	LL a = rd(0, c - 1);
	LL b = rd(0, c - 1);
	LL ans = floor_sum(n, a, b, c);
	LL brute = 0;
	REP(i, n) brute += (a * i + b) / c;
	assert(ans == brute);
}
