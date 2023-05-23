#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 100);
	int z = rd(1, int(1e6));
	assert((LL)n * n * z * z <= LL(1e18));
	vector<int> t(n);
	vector<LL> sum(n);
	REP (i, n)
		t[i] = rd(1, z);
	sum[0] = t[0];
	FOR (i, 1, n - 1)
		sum[i] = sum[i - 1] + t[i];
	int penalty = rd(0, n * z);
	penalty = rd(0, penalty);
	auto sm = [&](int l, int r) {
		return sum[r] - (l > 0 ? sum[l - 1] : 0);
	};
	function<LL(int, int)> cost = [&](int l, int r) {
		return sm(l, r) * sm(l, r) + penalty;
	};
	auto [score, cuts] = dp_1d1d(n, cost);
	vector<LL> dp(n);
	REP (i, n) {
		dp[i] = cost(0, i);
		REP (j, i)
			dp[i] = min(dp[i], dp[j] + cost(j + 1, i));
	}
	assert(dp[n - 1] == score);
	assert(ssize(cuts));
	REP (i, ssize(cuts) - 1)
		assert(cuts[i] < cuts[i + 1]);
	assert(cuts[0] >= 0);
	assert(cuts.back() == n - 1);
}

