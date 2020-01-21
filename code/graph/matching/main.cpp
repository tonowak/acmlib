/*
 * Opis: Turbo Matching
 * Czas: Średnio około O(n \log n), najgorzej O(n^2)
 * Użycie: wierzchołki grafu nie muszą być ładnie podzielone na dwia przedziały, musi być po prostu dwudzielny.
 */

vector<vector<int>> graph;
vector<int> match, vis;
int t = 0;
 
bool match_dfs(int v) {
	vis[v] = t;
	for(int u : graph[v])
		if(match[u] == -1) {
			match[u] = v;
			match[v] = u;
			return true;
		}
 
	for(int u : graph[v])
		if(vis[match[u]] != t && match_dfs(match[u])) {
			match[u] = v;
			match[v] = u;
			return true;
		}
	return false;
}
 
int match() {
	int n = int(graph.size());
	match.resize(n, -1);
	vis.resize(n);
 
	int ans = 0, d = -1;
	while(d != 0) {
		d = 0;
		++t;
		for(int v = 0; v < n; ++v)
			if(match[v] == -1)
				d += match_dfs(v);
		ans += d;
	}
	return ans;
}
