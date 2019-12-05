/*
 * Opis: template do Centroid Decomposition
 * Czas: O(n \log n)
 * Użycie:
 *   konstruktor - HLD(n, graf)
 *   swój kod wrzucamy do funkcji decomp
 */

struct CentroDecomp {
	vector<vector<int>> adj;
	vector<bool> done;
	vector<int> sub, par;
	CentroDecomp(int n, vector<vector<int>> &adj) 
		: adj(adj), vis(n), sub(n), par(n) {}

	void dfs(int v) {
		sub[v] = 1;
		for(int u : adj[v]) {
			if(!done[u] && u != par[v]) {
				par[u] = v; dfs(u);
				sub[v] += sub[u];
			}
		}
	}
	int centro(int v) {
		par[v] = -1; dfs(v);
		for(int sz = sub[v];;) {
			pair<int, int> mx = {0, 0};
			for(int u : adj[v])
				if(!done[u] && u != par[v])
					mx = max(mx, {sub[u], u});
			if(mx.first * 2 <= sz) return v;
			v = mx.second;
		}
	}
	vector<PII> cen;
	void decomp(int v) {
		done[v = centro(v)] = true;
		// kodzik idzie tutaj
		for(int u : adj[v]) 
			if(!done[u]) 
				decomp(u);
	}
};
