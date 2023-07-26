/*
 * Opis: O(n^3), wyznacznik macierzy (modulo lub double)
 */
#include "../matrix-header/main.cpp"
T determinant(vector<vector<T>>& a) {
	int n = ssize(a);
	T res = 1;
	REP(i, n) {
		int b = i;
		FOR(j, i + 1, n - 1)
			if(abs(a[j][i]) > abs(a[b][i]))
				b = j;
		if(i != b)
			swap(a[i], a[b]), res = sub(0, res);
		res = mul(res, a[i][i]);
		if (equal(res, 0))
			return 0;
		FOR(j, i + 1, n - 1) {
			T v = divide(a[j][i], a[i][i]);
			if (not equal(v, 0))
				FOR(k, i + 1, n - 1)
					a[j][k] = sub(a[j][k], mul(v, a[i][k]));
		}
	}
	return res;
}
