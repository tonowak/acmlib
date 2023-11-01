#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool is_prime(int x) {
	if (x < 2)
		return false;
	for (int i = 2; i * i <= x; ++i)
		if (x % i == 0)
			return false;
	return true;
}

void test() {
	const int limit = rd(0, 1) ? 1e3 : 1e5;

	int p;
	do {
		p = rd(1, limit);
	} while (not is_prime(p));
	int a = rd(0, p - 1);

	int ans = tonelli_shanks(a, p);
	debug(a, p, ans);

	if (ans == -1) {
		REP(i, p)
			assert(i * LL(i) % p != a);
	}
	else {
		assert(ans * LL(ans) % p == a);
	}
}
