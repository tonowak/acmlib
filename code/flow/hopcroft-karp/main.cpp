/* 
 * Opis: Hopcroft-Karp do liczenia matchingu. Przydaje się głównie w aproksymacji, ponieważ po $k$ iteracjach gwarantuje matching o rozmiarze przynajmniej $k/(k+1) \cdot$ best matching.
 * Użycie: wierzchołki grafu muszą być podzielone na warstwy 0..n0-1 oraz n0..n0+n1-1. Zwraca rozmiar matchingu oraz przypisanie (lub -1, gdy nie jest zmatchowane).
 * Czas: O(m \sqrt{n})
 */

pair<int, vector<int>> hopcroft_karp(vector<vector<int>> graph, int n0, int n1) {
	assert(n0 + n1 == ssize(graph));
	REP(v, n0 + n1)
		for(int u : graph[v])
			assert((v < n0) != (u < n0));

	vector<int> matched_with(n0 + n1, -1), dist(n0 + 1);
	constexpr int inf = int(1e9);
	vector<int> manual_que(n0 + 1);
 
	auto bfs = [&] {
		int head = 0, tail = -1;
		fill(dist.begin(), dist.end(), inf);
		REP(v, n0)
			if(matched_with[v] == -1) {
				dist[1 + v] = 0;
				manual_que[++tail] = v;
			}
		while(head <= tail) {
			int v = manual_que[head++];
			if(dist[1 + v] < dist[0])
				for(int u : graph[v])
					if(dist[1 + matched_with[u]] == inf) {
						dist[1 + matched_with[u]] = dist[1 + v] + 1;
						manual_que[++tail] = matched_with[u];
					}
		}
		return dist[0] != inf;
	};
 
	function<bool (int)> dfs = [&](int v) {
		if(v == -1)
			return true;
		for(auto u : graph[v])
			if(dist[1 + matched_with[u]] == dist[1 + v] + 1) {
				if(dfs(matched_with[u])) {
					matched_with[v] = u;
					matched_with[u] = v;
					return true;
				}
			}
		dist[1 + v] = inf;
		return false;
	};
 
	int answer = 0;
	for(int iter = 0; bfs(); ++iter)
		REP(v, n0)
			if(matched_with[v] == -1 and dfs(v))
				++answer;
	return {answer, matched_with};
}
