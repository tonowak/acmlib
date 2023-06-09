#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int test_type = rd(0, 1);
	int limit = test_type ? 3 : mod - 1;
	const int mn = 20;
	int n = rd(0, mn);
	int len = 3 * n + 5;
	vector<int> v(len), r(n);
	REP(i, n) {
		v[i] = rd(0, limit);
		r[i] = rd(0, limit);
	}
	FOR(i, n, len - 1)
		REP(j, n)
			v[i] = add(v[i], mul(v[i - j - 1], r[j]));
	int x_len = rd(0, 1) ? 2 * n : rd(2 * n, 3 * n);
	BerlekampMassey bm({v.begin(), v.begin() + x_len});
	REP(i, len)
		assert(v[i] == bm.get(i));
}
