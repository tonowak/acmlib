#include "main.cpp"
#include "../../utils/testing/test-wrapper.cpp"

bool test(int) {
	int test_type = rd(0, 1);
	LL limit = test_type ? LL(1e18) : LL(1e9);

	LL a = rd(-limit, limit), b = rd(-limit, limit);
	LL good_gcd = __gcd(a, b);
	LL gcd, x, y;
	tie(gcd, x, y) = extendedGcd(a, b);
	assert(gcd == good_gcd);

	if(test_type == 0)
		assert(a * x + b * y == gcd);
	debug(a, b, x, y, gcd);
	assert(abs(x) < abs(b) && abs(y) < abs(a));
	return false;
}
