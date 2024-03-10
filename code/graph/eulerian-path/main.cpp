/*
 * Opis: O(n), ścieżka eulera.
 * Krawędzie to pary $(to, id)$ gdzie $id$ dla grafu nieskierowanego jest takie samo dla $(u, v)$ i $(v, u)$.
 * 	 Graf musi być spójny, po zainicjalizowaniu w \texttt{path} jest ścieżka/cykl eulera, vector o długości $m + 1$ kolejnych wierzchołków
 * 	 Jeśli nie ma ścieżki/cyklu, \texttt{path} jest puste. Dla cyklu, \texttt{path[0] == path[m]}.
 */
struct EulerianPath {
	vector<pair<int, int>> edges;
	vector<vector<int>> adj;
	bool exists = true;
	int start = 0;
	vector<int> ids, vertices;
	vector<bool> used;
	int other(int v, int id) {
		auto [a, b] = edges[id];
		return v ^ a ^ b;
	}
	void dfs(int v) {
		while (ssize(adj[v])) {
			int id = adj[v].back(), u = other(v, id);
			adj[v].pop_back();
			if (used[id]) continue;
			used[id] = true;
			dfs(u);
			ids.emplace_back(id);
		}
	}
	EulerianPath(int n, const vector<pair<int, int>>& _edges, bool directed) : edges(_edges), adj(n), used(ssize(edges)) {
		vector<int> in(n);
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
				if (in[i] < ssize(adj[i]))
					start = i, ++cnt_in;
				else
					cnt_out += in[i] > ssize(adj[i]);
			}
			else if (ssize(adj[i]) % 2)
				start = i, ++cnt_in;
		}
		if (directed)
			REP(i, n)
				if (abs(ssize(adj[i]) - in[i]) > 1) {
					exists = false;
					return;
				}
		dfs(start);
		if (cnt_in + cnt_out > 2 or not all_of(used.begin(), used.end(), identity{})) {
			exists = false;
			return;
		}
		reverse(ids.begin(), ids.end());
		vertices = {start};
		for (int id : ids)
			vertices.emplace_back(other(vertices.back(), id));
	}
};
