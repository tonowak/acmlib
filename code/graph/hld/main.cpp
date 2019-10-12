/*
 * Opis: Heavy-Light Decomposition
 * Czas: O(\log n)
 * Pamięć : O(n)
 * Użycie:
 *   kontruktor - HLD(n, graph)
 *   lca(v, u) zwraca lca
 *   get_vertex(v) zwraca pozycję odpowiadającą wierzchołkowi
 *   get_path(v, u) zwraca przedziały do obsługiwania drzewem przedziałowym
 *   get_path(v, u) jeśli robisz operacje na wierzchołkach
 *   get_path(v, u, false) jeśli na krawędziach
 *   get_subtree(v, u) zwraca przedział odpowiadający podrzewu v
 */

struct HLD {
	vector<vector<int>> graph;
	vector<int> size, pre, pos, nxt, par;
	int t = 0;

	void init(int v, int p = -1) {
		par[v] = p;
		size[v] = 1;
		for(int &u : graph[v]) if(u != par[v]) {
			init(u, v);
			size[v] += size[u];
			if(size[u] > size[graph[v][0]])
				swap(u, graph[v][0]);
		}
	}

	void set_paths(int v) {
		pre[v] = t++;
		for(int &u : graph[v]) if(u != par[v]) {
			nxt[u] = (u == graph[v][0] ? nxt[v] : u);
			set_paths(u);
		}
		pos[v] = t;
	}

	HLD(int n, vector<vector<int>> graph, int root = 0)
		: graph(graph), size(n), pre(n), pos(n), nxt(n), par(n) {
		init(root);
		set_paths(root);
	}

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
		while(!path_u.empty()) {
			ret.emplace_back(path_u.back());
			path_u.pop_back();
		}
		return ret;
	}

	pair<int, int> get_subtree(int v) { return {pre[v], pos[v] - 1}; }
};
