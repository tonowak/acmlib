/*
 * Opis: O(m\;\alpha(n)), dla spójnego DAGu o jednym korzeniu root wyznacza listę synów
 *   w dominator tree (które jest drzewem, gdzie ojciec wierzchołka v
 *   to najbliższy wierzchołek, którego usunięcie powoduje,
 *   że już nie ma ścieżki od korzenia do v).
 * \texttt{dominator_tree(\{\{1,2\},\{3\},\{4\},\{4\},\{5\}\},0) == \{\{1,4,2\},\{3\},\{\},\{\},\{5\},\{\}\}\}}
 */
vector<vector<int>> dominator_tree(vector<vector<int>> dag, int root) {
	int n = ssize(dag);
	vector<vector<int>> t(n), rg(n), bucket(n);
	vector<int> id(n, -1), sdom = id, par = id, idom = id, dsu = id, label = id, rev = id;
	function<int (int, int)> find = [&](int v, int x) {
		if(v == dsu[v]) return x ? -1 : v;
		int u = find(dsu[v], x + 1);
		if(u < 0) return v;
		if(sdom[label[dsu[v]]] < sdom[label[v]]) label[v] = label[dsu[v]];
		dsu[v] = u;
		return x ? u : label[v];
	};
	int gtime = 0;
	function<void (int)> dfs = [&](int u) {
		rev[gtime] = u;
		label[gtime] = sdom[gtime] = dsu[gtime] = id[u] = gtime;
		gtime++;
		for(int w : dag[u]) {
			if(id[w] == -1) dfs(w), par[id[w]] = id[u];
			rg[id[w]].emplace_back(id[u]);
		}
	};
	dfs(root);
	for(int i = n - 1; i >= 0; i--) {
		for(int u : rg[i]) sdom[i] = min(sdom[i], sdom[find(u, 0)]);
		if(i > 0) bucket[sdom[i]].push_back(i);
		for(int w : bucket[i]) {
			int v = find(w, 0);
			idom[w] = (sdom[v] == sdom[w] ? sdom[w] : v);
		}
		if(i > 0) dsu[i] = par[i];
	}
	FOR(i, 1, n - 1) {
		if(idom[i] != sdom[i]) idom[i] = idom[idom[i]];
		t[rev[idom[i]]].emplace_back(rev[i]);
	}
	return t;
}
