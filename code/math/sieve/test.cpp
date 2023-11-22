#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	const int mx = 1e4;
	int n = rd(0, mx);

	sieve(n);

	auto is_composite = [&](int x) {
		if (x < 2)
			return false;
		for (int i = 2; i * i <= x; ++i)
			if (x % i == 0)
				return true;
		return false;
	};

	auto brute_primes = [&](int x) {
		vector <int> ans;
		FOR(i,2,x)
			if (not is_composite(i))
				ans.emplace_back(i);
		return ans;
	};
	assert(primes == brute_primes(n));

	auto brute_comp = [&](int x) {
		vector<bool> ans(x + 1);
		FOR(i, 0, x)
			ans[i] = is_composite(i);
		return ans;
	};
	assert(comp == brute_comp(n));

	auto brute_prime_div = [&](int x) {
		vector<int> ans(x + 1);
		for (int i = x; i >= 2; --i) {
			if (is_composite(i))
				continue;
			for (int j = i; j <= x; j += i)
				ans[j] = i;
		}
		return ans;
	};
	assert(prime_div == brute_prime_div(n));
}
