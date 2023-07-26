/*
 * Opis: O(n + matching(n, m)) wyznaczanie w grafie dwudzielnym kolejno minimalnego pokrycia krawędziowego (PK), maksymalnego zbioru niezależnych wierzchołków (NW), minimalnego pokrycia wierzchołkowego (PW) pokorzystając z maksymalnego zbioru niezależnych krawędzi (NK) (tak zwany matching). Z tw. Koniga zachodzi |NK|=n-|PK|=n-|NW|=|PW|.
 */
#include "../matching/main.cpp"

vector<pair<int, int>> get_min_edge_cover(vector<vector<int>> graph) {
	vector<int> match = Matching(graph)().second;
	vector<pair<int, int>> ret;
	REP(v, ssize(match))
		if(match[v] != -1 and v < match[v])
			ret.emplace_back(v, match[v]);
		else if(match[v] == -1 and not graph[v].empty())
			ret.emplace_back(v, graph[v].front());
	return ret;
}

array<vector<int>, 2> get_coloring(vector<vector<int>> graph) {
	int n = ssize(graph);
	vector<int> match = Matching(graph)().second;
	vector<int> color(n, -1);
	function<void (int)> dfs = [&](int v) {
		color[v] = 0;
		for(int u : graph[v])
			if(color[u] == -1) {
				color[u] = true;
				dfs(match[u]);
			}
	};
	REP(v, n)
		if(match[v] == -1)
			dfs(v);
	REP(v, n)
		if(color[v] == -1)
			dfs(v);
	array<vector<int>, 2> groups;
	REP(v, n)
		groups[color[v]].emplace_back(v);
	return groups;
}

vector<int> get_max_independent_set(vector<vector<int>> graph) {
	return get_coloring(graph)[0];
}

vector<int> get_min_vertex_cover(vector<vector<int>> graph) {
	return get_coloring(graph)[1];
}
