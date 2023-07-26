/*
 * Opis: O(n), ścieżka eulera.
 * Krawędzie to pary $(to, id)$ gdzie $id$ dla grafu nieskierowanego jest takie samo dla $(u, v)$ i $(v, u)$.
 * 	 Graf musi być spójny, po zainicjalizowaniu w \texttt{path} jest ścieżka/cykl eulera, vector o długości $m + 1$ kolejnych wierzchołków
 * 	 Jeśli nie ma ścieżki/cyklu, \texttt{path} jest puste. Dla cyklu, \texttt{path[0] == path[m]}.
 */
using PII = pair<int, int>;
struct EulerianPath {
	vector<vector<PII>> adj;
	vector<bool> used;
	vector<int> path;
	void dfs(int v) {
		while(!adj[v].empty()) {
			auto [u, id] = adj[v].back();
			adj[v].pop_back();
			if(used[id]) continue;
			used[id] = true;
			dfs(u);
		}
		path.emplace_back(v);
	}
	EulerianPath(vector<vector<PII>> _adj, bool directed = false) : adj(_adj) {
		int s = 0, m = 0;
		vector<int> in(ssize(adj));
		REP(i, ssize(adj)) for(auto [j, id] : adj[i]) in[j]++, m++;
		REP(i, ssize(adj)) if(directed) {
			if(in[i] < ssize(adj[i])) s = i;
		} else {
			if(ssize(adj[i]) % 2) s = i;
		}
		m /= (2 - directed);
		used.resize(m); dfs(s);
		if(ssize(path) != m + 1) path.clear();
		reverse(path.begin(), path.end());
	}
};
