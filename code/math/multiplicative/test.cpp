#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	const int mx = 1e3;
	int n = rd(0, mx);

	auto brute_mobius = [&](int x) {
		vector<int> ans(x + 1, 1);
		ans[0] = 0; // only for testing
		FOR(i, 1, x) {
			int y = i;
			for (int j = 2; j * j <= y; ++j) {
				int cnt = 0;
				while (y % j == 0) {
					y /= j;
					++cnt;
				}
				if (cnt >= 2)
					ans[i] = 0;
				else if (cnt == 1)
					ans[i] = -ans[i];
			}
			if (y > 1)
				ans[i] = -ans[i];
		}
		return ans;
	};
	assert(mobius(n) == brute_mobius(n));

	auto brute_totient = [&](int x) {
		vector<int> ans(x + 1);
		ans[0] = 1; // only for testing
		FOR(i, 1, x)
			FOR(j, 1, i)
				ans[i] += gcd(i, j) == 1;
		return ans;
	};
	assert(totient(n) == brute_totient(n));
}
