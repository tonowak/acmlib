/*
 * Opis: Range Minimum Query z użyciem sparse table
 * Czas: O(n \log n)
 * Pamięć: O(n \log n)
 * Użycie:
 *    RMQ(vec) tworzy sparse table na ciągu vec
 *    query(l, r) odpowiada na RMQ w O(1)
 */

struct RMQ {
	vector<vector<int>> st;
	vector<int> pre;
	RMQ(vector<int> &a) {
		int n = size(a), lg = 0;
		while((1 << lg) < n) lg++;
		st.resize(lg + 1, vector<int>(a));
		st[0] = a;
		FOR(i, 1, lg) REP(j, n) {
			st[i][j] = st[i - 1][j];
			int q = j + (1 << (i - 1));
			if(q < n) st[i][j] = min(st[i][j], st[i - 1][q]);
		}
		pre.resize(n + 1);
		FOR(i, 2, n) pre[i] = pre[i / 2] + 1;
	}
 
	int query(int l, int r) {
		int q = pre[r - l + 1], x = r - (1 << q) + 1;
		return min(st[q][l], st[q][x]);
	}
};
