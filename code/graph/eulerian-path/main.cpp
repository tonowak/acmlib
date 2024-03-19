/*
 * Opis: O(n + m), ścieżka eulera. Zwraca tupla (exists, ids, vertices).
 * W \texttt{exists} jest informacja czy jest ścieżka/cykl eulera,
 * \texttt{ids} zawiera id kolejnych krawędzi,
 * \texttt{vertices} zawiera listę wierzchołków na tej ścieżce.
 * Dla cyklu, \texttt{vertices[0] == vertices[m]}.
 */
tuple<bool, vector<int>, vector<int>> eulerian_path(int n, const vector<pair<int, int>> &edges, bool directed) {
	vector<int> in(n);
	vector<vector<int>> adj(n);
	int start = 0;
	REP(i, ssize(edges)) {
		auto [a, b] = edges[i];
		start = a;
		++in[b];
		adj[a].emplace_back(i);
		if (not directed)
			adj[b].emplace_back(i);
	}
	int cnt_in = 0, cnt_out = 0;
	REP(i, n) {
		if (directed) {
			if (abs(ssize(adj[i]) - in[i]) > 1)
				return {};
			if (in[i] < ssize(adj[i]))
				start = i, ++cnt_in;
			else
				cnt_out += in[i] > ssize(adj[i]);
		}
		else if (ssize(adj[i]) % 2)
			start = i, ++cnt_in;
	}
	vector<int> ids, vertices;
	vector<bool> used(ssize(edges));
	function<void (int)> dfs = [&](int v) {
		while (ssize(adj[v])) {
			int id = adj[v].back(), u = v ^ edges[id].first ^ edges[id].second;
			adj[v].pop_back();
			if (used[id]) continue;
			used[id] = true;
			dfs(u);
			ids.emplace_back(id);
		}
	};
	dfs(start);
	if (cnt_in + cnt_out > 2 or not all_of(used.begin(), used.end(), identity{}))
		return {};
	reverse(ids.begin(), ids.end());
	if (ssize(ids))
		vertices = {start};
	for (int id : ids)
		vertices.emplace_back(vertices.back() ^ edges[id].first ^ edges[id].second);
	return {true, ids, vertices};
}
