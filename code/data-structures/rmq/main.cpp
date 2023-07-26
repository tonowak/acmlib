/*
 * Opis: O(n \log n) czasowo i pamięciowo, Range Minimum Query z użyciem sparse table,
 *   zapytanie jest w O(1).
 */

struct RMQ {
	vector<vector<int>> st;
	RMQ(const vector<int> &a) {
		int n = ssize(a), lg = 0;
		while((1 << lg) < n) lg++;
		st.resize(lg + 1, a);
		FOR(i, 1, lg) REP(j, n) {
			st[i][j] = st[i - 1][j];
			int q = j + (1 << (i - 1));
			if(q < n) st[i][j] = min(st[i][j], st[i - 1][q]);
		}
	}
	int query(int l, int r) {
		int q = __lg(r - l + 1), x = r - (1 << q) + 1;
		return min(st[q][l], st[q][x]);
	}
};
