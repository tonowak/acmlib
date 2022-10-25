#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	static bool done = false;
	if (not done) {
		assert(add(mod - 1, mod - 1) == mod - 2);
		assert(sub(0, mod - 1) == 1);
		assert(sub(mod - 1, 0) == mod - 1);
		assert(sub(mod - 1, mod - 1) == 0);
		assert(mul(mod - 1, mod - 1) == 1);
		FOR(i, 1, 100) {
			assert(mul(inv(i), i) == 1);
			assert(mul(inv(mod - i), mod - i) == 1);
		}
		done = true;
	}

	const int mn = 100;
	const int mq = 100;
	int n = rd(1, mn);
	int q = rd(1, mq);

	BinomCoeff bc(n);
	vector brute(n + 1, vector (n + 1, 0));
	FOR(i, 0, n)
		brute[i][0] = brute[i][i] = 1;
	FOR(i, 1, n)
		FOR(j, 1, i - 1)
			brute[i][j] = add(brute[i - 1][j], brute[i - 1][j - 1]);

	REP(qq, q) {
		int a = rd(0, n);
		int b = rd(0, a);
		assert(bc(a, b) == brute[a][b]);
	}
}
