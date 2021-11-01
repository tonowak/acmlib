#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int mx = 1e4;
	int n = rd(0, mx);
	prime.clear();
	sieve(n);
	auto f = [&](int x) {
		vector <int> ans;
		FOR(i,2,x) {
			bool is_prime = true;
			for (int j = 2; j * j <= i; ++j)
				if (i % j == 0) {
					is_prime = false;
					break;
				}
			if (is_prime)
				ans.emplace_back(i);
		}
		return ans;
	};
	assert(prime == f(n));
}
