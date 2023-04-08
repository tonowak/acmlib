#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	const int mn = 10;
	int n = rd(1, mn);
	vector a(n, vector(n, T(0)));
	const int limit = rd(0, 1) ? 3 : mod - 1;
	REP(i, n)
		REP(j, n)
			a[i][j] = rd(0, limit);
	auto inva = a;
	int rank = inverse(inva);
	debug(rank, a);
	assert(rank >= 0 and rank <= n);
	if (rank == n) {
		debug(inva);
		REP(i, n) {
			REP(j, n) {
				T sum = 0;
				REP(k, n)
					sum = add(sum, mul(a[i][k], inva[k][j]));
				assert(equal(sum, i == j));
			}
		}
	}
}
