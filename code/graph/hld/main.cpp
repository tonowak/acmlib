/*
 * Opis: O(q \log n) Heavy-Light Decomposition.
 *   \texttt{get\_vertex(v)} zwraca pozycję odpowiadającą wierzchołkowi.
 *   \texttt{get\_path(v, u)} zwraca przedziały do obsługiwania drzewem przedziałowym.
 *   \texttt{get\_path(v, u)} jeśli robisz operacje na wierzchołkach.
 *   \texttt{get\_path(v, u, false)} jeśli na krawędziach (nie zawiera lca).
 *   \texttt{get\_subtree(v)} zwraca przedział preorderów odpowiadający podrzewu v.
 */
struct HLD {
	// BEGIN HASH
	vector<vector<int>> &adj;
	vector<int> sz, pre, pos, nxt, par;
	int t = 0;
	void init(int v, int p = -1) {
		par[v] = p;
		sz[v] = 1;
		if(ssize(adj[v]) > 1 && adj[v][0] == p)
			swap(adj[v][0], adj[v][1]);
		for(int &u : adj[v]) if(u != par[v]) {
			init(u, v);
			sz[v] += sz[u];
			if(sz[u] > sz[adj[v][0]])
				swap(u, adj[v][0]);
		}
	}
	void set_paths(int v) {
		pre[v] = t++;
		for(int &u : adj[v]) if(u != par[v]) {
			nxt[u] = (u == adj[v][0] ? nxt[v] : u);
			set_paths(u);
		}
		pos[v] = t;
	}
	HLD(int n, vector<vector<int>> &_adj)
		: adj(_adj), sz(n), pre(n), pos(n), nxt(n), par(n) {
		init(0), set_paths(0);
	} // END HASH
	int lca(int v, int u) {
		while(nxt[v] != nxt[u]) {
			if(pre[v] < pre[u])
				swap(v, u);
			v = par[nxt[v]];
		}
		return (pre[v] < pre[u] ? v : u);
	}
	vector<pair<int, int>> path_up(int v, int u) {
		vector<pair<int, int>> ret;
		while(nxt[v] != nxt[u]) {
			ret.emplace_back(pre[nxt[v]], pre[v]);
			v = par[nxt[v]];
		}
		if(pre[u] != pre[v]) ret.emplace_back(pre[u] + 1, pre[v]);
		return ret;
	}
	int get_vertex(int v) { return pre[v]; }
	vector<pair<int, int>> get_path(int v, int u, bool add_lca = true) {
		int w = lca(v, u);
		auto ret = path_up(v, w);
		auto path_u = path_up(u, w);
		if(add_lca) ret.emplace_back(pre[w], pre[w]);
		ret.insert(ret.end(), path_u.begin(), path_u.end());
		return ret;
	}
	pair<int, int> get_subtree(int v) { return {pre[v], pos[v] - 1}; }
};
