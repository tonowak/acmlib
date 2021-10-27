#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	vector <LL> v = {
		2047ll,
		1373653ll,
		25326001ll,
		3215031751ll,
		2152302898747ll,
		3474749660383ll,
		341550071728321ll,
		3825123056546413051ll
	};
	static int counter1 = ssize(v);
	if (counter1 > 0) {
		--counter1;
		assert(!miller_rabin(v[counter1]));
		return;
	}
	auto brute = [&](LL x) {
		if (x <= 1) return false;
		for (LL i = 2; i * i <= x; ++i) {
			if (x % i == 0) return false;
		}
		return true;
	};
	static int counter2 = 1e5;
	if (counter2 >= 0) {
		assert(miller_rabin(counter2) == brute(counter2));
		--counter2;
		return;
	}
	LL mn = (1ll << 40);
	LL n = rd_ll(0, mn);
	assert(miller_rabin(n) == brute(n));
}
