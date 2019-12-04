/*
 * Opis: Ścieżka eulera
 * Czas: O(n)
 * Użycie: Krawędzie to pary (to, id) gdzie id dla grafu nieskierowanego jest takie samo dla (u, v) i (v, u)
 * 	 Graf musi być spójny, po zainicjalizowaniu w .path jest ścieżka/cykl eulera, vector o długości m + 1 kolejnych wierzchołków
 * 	 Jeśli nie ma ścieżki/cyklu, path jest puste. Dla cyklu, path[0] == path[m]
 */

using PII = pair<int, int>;
struct EulerianPath {
	vector<vector<PII>> adj;
	vector<bool> used;
	vector<int> path;
	void dfs(int v) {
		while(!adj[v].empty()) {
			int u, id; tie(u, id) = adj[v].back();
			adj[v].pop_back();
			if(used[id]) continue;
			used[id] = true;
			dfs(u);
		}
		path.emplace_back(v);
	}
	EulerianPath(int m, vector<vector<PII>> &adj) : adj(adj) {
		used.resize(m); dfs(0);
		if(size(path) != m + 1) path.clear();
		reverse(path.begin(), path.end());
	}
};
