#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool test(int)
{
	int mx = 10;
	LL n = rd(2, 10);
	LL a = rd(0, n - 1);
	LL m = rd(2, 10);
	LL b = rd(0, m - 1);
	if(__gcd(n, m) != 1) return 0;
	LL x = crt(a, n, b, m);
	debug(a, n, b, m, x);
	return !(x % n == a and x % m == b);
}
