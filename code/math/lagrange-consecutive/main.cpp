/*
 * Opis: O(n), przyjmuje wartości wielomianu w punktach $0,1,\dots$ i wylicza jego wartość w $x$. lagrange\_consecutive(\{2, 3, 4\}, 3) == 5
 */
#include "../simple-modulo/main.cpp"
int lagrange_consecutive(vector<int> y, int x) {
	int n = ssize(y), fac = 1, pref = 1, suff = 1, ret = 0;
	FOR(i, 1, n) fac = mul(fac, i);
	fac = inv(fac);
	REP(i, n) {
		fac = mul(fac, n - i);
		y[i] = mul(y[i], mul(pref, fac));
		y[n - 1 - i] = mul(y[n - 1 - i], mul(suff, mul(i % 2 ? mod - 1 : 1, fac)));
		pref = mul(pref, sub(x, i));
		suff = mul(suff, sub(x, n - 1 - i));
	}
	REP(i, n) ret = add(ret, y[i]);
	return ret;
}
