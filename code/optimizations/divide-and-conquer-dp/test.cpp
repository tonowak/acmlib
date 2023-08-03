#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int m = rd(1, 10);
	vector cost(m, vector<LL>(m));
	REP(i, m)
		FOR(j, i, m - 1)
			cost[i][j] = rd(-10, 10);

	auto check_valid_c = [&] {
		REP(a, m)
			FOR(b, a, m - 1)
				FOR(c, b, m - 1)
					FOR(d, c, m - 1) {
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

	int n = rd(1, 10);
	vector dp(n + 1, vector(m, numeric_limits<LL>::max()));
	dp[0] = cost[0];
	FOR(i, 1, n) {
		REP(j, m) {
			REP(k, j + 1) {
				dp[i][j] = min(dp[i][j], (k ? dp[i - 1][k - 1] : 0) + cost[k][j]);
			}
		}
	}
	debug(dp);

	auto got = divide_and_conquer_optimization(n, m, [&](int k, int j) { return cost[k][j]; });
	debug(got, dp[n]);
	assert(got == dp[n]);
}
