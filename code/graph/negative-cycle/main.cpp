/*
 * Opis: Wyznaczanie ujemnego cyklu (i stwierdzanie czy istnieje)
 * Czas: O(nm)
 * Użycie:
 *   [exists_negative, cycle] = negative_cycle(digraph);
 *   cycle spełnia własność, że istnieje krawędź cycle[i]->cycle[(i+1)%ssize(cycle)].
 *   Żeby wyznaczyć krawędzie na cyklu, wystarczy wybierać najtańszą krawędź między wierzchołkami.
 */

template</*integral*/class I>
pair<bool, vector<int>> negative_cycle(vector<vector<pair<int, I>>> graph) {
	int n = ssize(graph);
	vector<I> dist(n);
	vector<int> from(n, -1);
	int v_on_cycle = -1;
	REP(iter, n) {
		v_on_cycle = -1;
		REP(v, n)
			for(auto [u, w] : graph[v])
				if(dist[u] > dist[v] + w) {
					dist[u] = dist[v] + w;
					from[u] = v;
					v_on_cycle = u;
				}
	}
	if(v_on_cycle == -1)
		return {false, {}};

	REP(iter, n)
		v_on_cycle = from[v_on_cycle];
	vector<int> cycle = {v_on_cycle};
	for(int v = from[v_on_cycle]; v != v_on_cycle; v = from[v])
		cycle.emplace_back(v);
	reverse(cycle.begin(), cycle.end());
	return {true, cycle};
}
