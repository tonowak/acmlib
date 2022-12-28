#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 10);
	vector cost(n, vector<LL>(n));
	REP(i, n)
		FOR(j, i, n - 1)
			cost[i][j] = rd(-10, 10);

	auto check_valid_c = [&] {
		REP(a, n)
			FOR(b, a, n - 1)
				FOR(c, b, n - 1)
					FOR(d, c, n - 1) {
						if(cost[b][c] > cost[a][d])
							return false;
						if(cost[a][c] + cost[b][d] > cost[a][d] + cost[b][c])
							return false;
					}
		return true;
	};
	if(not check_valid_c())
		return;
	debug(cost);

	vector dp(n, vector(n, int(1e9)));
	REP(i, n)
		dp[i][i] = int(cost[i][i]);
	FOR(len, 2, n)
		REP(l, n - len + 1) {
			int r = l + len - 1;
			FOR(k, l, r - 1)
				dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + int(cost[l][r]));
		}
	debug(dp);

	LL got = knuth_optimization(cost);
	debug(got, dp[0][n - 1]);
	assert(dp[0][n - 1] == got);
}
