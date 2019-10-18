/*
 * Opis: Floyd-Warshall
 * Czas: O(n^3)
 * Użycie:
 *   FloydWarshall(graph) zwraca macież odległości
 *   graph to macierz sąsiedztwa z wagami
 */

vector<vector<LL>> FloydWarshall(vector<vector<int>> graph) {
	int n = size(graph);
	vector<vector<LL>> dist(n, vector<LL>(n, 1e18));
	REP(k, n) REP(i, n) REP(j, n)
		dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
