/*
 * Opis: Średnio około O(n \log n), najgorzej O(n^2).
 *   Wierzchołki grafu nie muszą być ładnie podzielone na dwia przedziały, musi być po prostu dwudzielny.
 *   Na przykład \texttt{auto [match\_size, match] = Matching(graph)();}
 */

struct Matching {
	vector<vector<int>> &adj;
	vector<int> mat, vis;
	int t = 0, ans = 0;
	bool mat_dfs(int v) {
		vis[v] = t;
		for(int u : adj[v])
			if(mat[u] == -1) {
				mat[u] = v;
				mat[v] = u;
				return true;
			}
		for(int u : adj[v])
			if(vis[mat[u]] != t && mat_dfs(mat[u])) {
				mat[u] = v;
				mat[v] = u;
				return true;
			}
		return false;
	}
	Matching(vector<vector<int>> &_adj) : adj(_adj) {
		mat = vis = vector<int>(ssize(adj), -1);
	}
	pair<int, vector<int>> operator()() {
		int d = -1;
		while(d != 0) {
			d = 0, ++t;
			REP(v, ssize(adj))
				if(mat[v] == -1)
					d += mat_dfs(v);
			ans += d;
		}
		return {ans, mat};
	}
};
