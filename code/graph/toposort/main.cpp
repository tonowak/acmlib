/*
 * Opis: Wyznacza sortowanie topologiczne w DAGu.
 * Czas: O(n)
 * Użycie:
 *   get_toposort_order(g) zwraca listę wierzchołków takich, że krawędzie są od wierzchołków wcześniejszych w liście do późniejszych.
 *   get_new_vertex_id_from_order(order) zwraca odwrotność tej permutacji, tzn. dla każdego wierzchołka trzyma jego nowy numer, aby po przenumerowaniu grafu istniały krawędzie tylko do wierzchołków o większych numerach.
 *   permute(elems, new_id) zwraca przepermutowaną tablicę elems według nowych numerów wierzchołków (przydatne jak się trzyma informacje o wierzchołkach, a chce się zrobić przenumerowanie topologiczne).
 *   renumerate_vertices(...) zwraca nowy graf, w którym wierzchołki są przenumerowane.
 */

vector<int> get_toposort_order(vector<vector<int>> graph) {
	int n = ssize(graph);
	vector<int> indeg(n);
	REP(v, n)
		for(int u : graph[v])
			++indeg[u];
	vector<int> que;
	REP(v, n)
		if(indeg[v] == 0)
			que.emplace_back(v);
	vector<int> ret;
	while(not que.empty()) {
		int v = que.back();
		que.pop_back();
		ret.emplace_back(v);
		for(int u : graph[v])
			if(--indeg[u] == 0)
				que.emplace_back(u);
	}
	return ret;
}

vector<int> get_new_vertex_id_from_order(vector<int> order) {
	vector<int> ret(ssize(order), -1);
	REP(v, ssize(order))
		ret[order[v]] = v;
	return ret;
}

template<class T>
vector<T> permute(vector<T> elems, vector<int> new_id) {
	vector<T> ret(ssize(elems));
	REP(v, ssize(elems))
		ret[new_id[v]] = elems[v];
	return ret;
}

vector<vector<int>> renumerate_vertices(vector<vector<int>> graph, vector<int> new_id) {
	int n = ssize(graph);
	vector<vector<int>> ret(n);
	REP(v, n)
		for(int u : graph[v])
			ret[new_id[v]].emplace_back(new_id[u]);
	REP(v, n)
		for(int u : ret[v])
			assert(v < u);
	return ret;
}

// graph = renumerate_vertices(graph, get_new_vertex_id_from_order(get_toposort_order(graph)));
