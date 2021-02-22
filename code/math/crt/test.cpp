#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	LL mx = 10;
	LL n = rd(2, mx);
	LL a = rd(0, n - 1);
	LL m = rd(2, mx);
	LL b = rd(0, m - 1);
	if(__gcd(n, m) != 1) return;
	LL x = crt(a, n, b, m);
	debug(a, n, b, m, x);
	assert(x % n == a and x % m == b);
}
