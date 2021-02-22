#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	LL a = rd(0, 4);
	int b = rd(0, 3);
	int m = rd(0, 1e9);
	int ex = 1;
	a %= m;
	REP(i, b)
		ex = ex * a % m;
	debug(a, b, m, ex);
	assert(ex == exp(a, b, m));
}
