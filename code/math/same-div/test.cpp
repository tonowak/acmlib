#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto brute_floor = [&](LL n) -> vector<pair<LL, LL>> {
		vector<pair<LL, LL>> v;
		for (LL i = 1; i <= n; ++i) {
			LL x = i + 1;
			while (x <= n and n / x == n / i)
				++x;
			v.emplace_back(i, x - 1);
			i = x - 1;
		}
		return v;
	};

	auto brute_ceil = [&](LL n) -> vector<pair<LL, LL>> {
		vector<pair<LL, LL>> v;
		for (LL i = n; i >= 1; --i) {
			LL x = i - 1;
			while (x >= 1 and (n + x - 1) / x == (n + i - 1) / i)
				--x;
			v.emplace_back(x + 1, i);
			i = x + 1;
		}
		return v;
	};

	const int max_n = rd(0, 1) ? 1e2 : 1e5;
	{ // test same_floor
		int n = rd(1, max_n);
		auto v = same_floor(n);
		auto vbrute = brute_floor(n);
		assert(v == vbrute);
	}

	{ // test same_ceil
		int n = rd(1, max_n);
		auto v = same_ceil(n);
		auto vbrute = brute_ceil(n);
		assert(v == vbrute);
	}
}
