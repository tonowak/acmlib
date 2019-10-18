/*
 * Opis: Turbo Matching
 * Czas: Mniej więcej O(n \log n), najgorzej O(n^2)
 * Użycie: wierzchołki grafu nie muszą być ładnie podzielone na dwia przedziały, musi być po prostu dwudzielny. Funkcja match() działa w o(n), nieważne jak małe zmiany się wprowadzi do aktualnego matchingu.
 */

vector<vector<int>> graph;
vector<int> matched, visited;
int clear_time = 0;
 
bool match_DFS(int v) {
	visited[v] = clear_time;
	for(int u : graph[v])
		if(matched[u] == -1) {
			matched[u] = v;
			matched[v] = u;
			return true;
		}
 
	for(int u : graph[v])
		if(visited[matched[u]] != clear_time && match_DFS(matched[u])) {
			matched[u] = v;
			matched[v] = u;
			return true;
		}
	return false;
}
 
int match() {
	int n = int(graph.size());
	matched.resize(n, -1);
	visited.resize(n);
 
	int delta = -1;
	while(delta != 0) {
		delta = 0;
		++clear_time;
		for(int v = 0; v < n; ++v)
			if(matched[v] == -1)
				delta += match_DFS(v);
	}
	int answer = 0;
	for(int v = 0; v < n; ++v)
		if(matched[v] != -1)
			++answer;
	return answer / 2;
}
