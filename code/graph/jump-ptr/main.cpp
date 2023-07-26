/*
 * Opis: O((n+q) \log n),
 *   \texttt{jump\_up(v, k)} zwraca wierzchołek o $k$ krawędzi wyżej niż $v$ lub $-1$.
 *   \texttt{OperationJumpPtr} może otrzymać wynik na ścieżce.
 *   Wynik na ścieżce do góry wymaga łączności, wynik dowolnej ścieżki jest poprawny, gdy jest odwrotność wyniku lub przemienna.
 */

struct SimpleJumpPtr {
	int bits;
	vector<vector<int>> graph, jmp;
	vector<int> par, dep;
	void par_dfs(int v) {
		for(int u : graph[v])
			if(u != par[v]) {
				par[u] = v;
				dep[u] = dep[v] + 1;
				par_dfs(u);
			}
	}
	SimpleJumpPtr(vector<vector<int>> g = {}, int root = 0) : graph(g) {
		int n = ssize(graph);
		bits = __lg(max(1, n)) + 1;
		dep.resize(n);
		par.resize(n, -1);
		if(n > 0)
			par_dfs(root);
		jmp.resize(bits, vector<int>(n, -1));
		jmp[0] = par;
		FOR(b, 1, bits - 1)
			REP(v, n)
				if(jmp[b - 1][v] != -1)
					jmp[b][v] = jmp[b - 1][jmp[b - 1][v]];
		debug(graph, jmp);
	}
	int jump_up(int v, int h) {
		for(int b = 0; (1 << b) <= h; ++b)
			if((h >> b) & 1)
				v = jmp[b][v];
		return v;
	}
	int lca(int v, int u) {
		if(dep[v] < dep[u])
			swap(v, u);
		v = jump_up(v, dep[v] - dep[u]);
		if(v == u)
			return v;

		for(int b = bits - 1; b >= 0; b--) {
			if(jmp[b][v] != jmp[b][u]) {
				v = jmp[b][v];
				u = jmp[b][u];
			}
		}
		return par[v];
	}
};

using PathAns = LL;
PathAns merge(PathAns down, PathAns up) {
	return down + up;
}

struct OperationJumpPtr {
	SimpleJumpPtr ptr;
	vector<vector<PathAns>> ans_jmp;

	OperationJumpPtr(vector<vector<pair<int, int>>> g, int root = 0) {
		debug(g, root);
		int n = ssize(g);
		vector<vector<int>> unweighted_g(n);
		REP(v, n)
			for(auto [u, w] : g[v]) {
				(void) w;
				unweighted_g[v].emplace_back(u);
			}
		ptr = SimpleJumpPtr(unweighted_g, root);
		ans_jmp.resize(ptr.bits, vector<PathAns>(n));
		REP(v, n)
			for(auto [u, w] : g[v])
				if(u == ptr.par[v])
					ans_jmp[0][v] = PathAns(w);
		FOR(b, 1, ptr.bits - 1)
			REP(v, n)
				if(ptr.jmp[b - 1][v] != -1 and ptr.jmp[b - 1][ptr.jmp[b - 1][v]] != -1)
					ans_jmp[b][v] = merge(ans_jmp[b - 1][v], ans_jmp[b - 1][ptr.jmp[b - 1][v]]);
	}
	PathAns path_ans_up(int v, int h) {
		PathAns ret = PathAns();
		for(int b = ptr.bits - 1; b >= 0; b--)
			if((h >> b) & 1) {
				ret = merge(ret, ans_jmp[b][v]);
				v = ptr.jmp[b][v];
			}
		return ret;
	}
	PathAns path_ans(int v, int u) { // discards order of edges on path
		int l = ptr.lca(v, u);
		return merge(
			path_ans_up(v, ptr.dep[v] - ptr.dep[l]),
			path_ans_up(u, ptr.dep[u] - ptr.dep[l])
		);
	}
};
