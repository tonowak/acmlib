/*
 * Opis: O(n^3), odwrotność macierzy (modulo lub double). Zwraca rząd macierzy.
 * Dla odwracalnych macierzy (rząd = n) w $a$ znajdzie się jej odwrotność.
 */

#include "../matrix-header/main.cpp"

int inverse(vector<vector<T>>& a) {
	int n = ssize(a);
	vector<int> col(n);
	vector h(n, vector<T>(n));
	REP(i, n)
		h[i][i] = 1, col[i] = i;
	REP(i, n) {
		int r = i, c = i;
		FOR(j, i, n - 1) FOR(k, i, n - 1)
			if(abs(a[j][k]) > abs(a[r][c]))
				r = j, c = k;
		if (equal(a[r][c], 0))
			return i;
		a[i].swap(a[r]);
		h[i].swap(h[r]);
		REP(j, n)
			swap(a[j][i], a[j][c]), swap(h[j][i], h[j][c]);
		swap(col[i], col[c]);
		T v = a[i][i];
		FOR(j, i + 1, n - 1) {
			T f = divide(a[j][i], v);
			a[j][i] = 0;
			FOR(k, i + 1, n - 1)
				a[j][k] = sub(a[j][k], mul(f, a[i][k]));
			REP(k, n)
				h[j][k] = sub(h[j][k], mul(f, h[i][k]));
		}
		FOR(j, i + 1, n - 1)
			a[i][j] = divide(a[i][j], v);
		REP(j, n)
			h[i][j] = divide(h[i][j], v);
		a[i][i] = 1;
	}
	for(int i = n - 1; i > 0; --i) REP(j, i) {
		T v = a[j][i];
		REP(k, n)
			h[j][k] = sub(h[j][k], mul(v, h[i][k]));
	}
	REP(i, n)
		REP(j, n)
			a[col[i]][col[j]] = h[i][j];
	return n;
}
