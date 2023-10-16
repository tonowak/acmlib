#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto eval = [&](const vector<int>& a, int x) {
		int ret = 0, p = 1;
		REP(i, ssize(a)) {
			ret = add(ret, mul(a[i], p));
			p = mul(p, x);
		}
		return ret;
	};
	const int z = rd(0, 1) ? 5 : mod - 1;
	const int n = rd(0, 30);
	const int x = rd(0, 2 * n);
	vector<int> a(n);
	REP(i, n)
		a[i] = rd(0, z);
	vector<int> y(n);
	REP(i, n)
		y[i] = eval(a, i);
	debug(a, x, y, eval(a, x));
	assert(lagrange_consecutive(y, x) == eval(a, x));
}
