/*
 * Opis: Ścieżka eulera
 * Czas: O(n)
 * Użycie:
 *   krawędzie to pary (to, id) gdzie id dla grafu nieskierowanego jest
 *   takie samo dla (u, v) i (v, u)
 * 	 konstruktor - EulerianPath(m, graph)
 * 	 graf musi być spójny
 *   get_path() zwraca ścieżkę eulera
 *   get_cycle() zwraca cykl eulera
 *   jeśli nie ma, obie funkcję zwrócą pusty vector
 */

struct EulerianPath {
	vector<vector<pair<int, int>>> graph;
	vector<bool> used;
	vector<int> in, out;
	vector<int> path, cycle

	void dfs(int v = 0) {
		in[v]++;
		while(!graph[v].empty()) {
			auto edge = graph[v].back();
			graph[v].pop_back();
			int u = edge.first;
			int id = edge.second;
			if(used[id]) continue;
			used[id] = true;
			out[v]++;
			dfs(u);
		}
		path.emplace_back(v);
	}

	EulerianPath(int m, vector<vector<pair<int, int>>> &graph) : graph(graph) {
		int n = size(graph);
		used.resize(m);
		in.resize(n);
		out.resize(n);

		dfs();
		in[0]--;
		debug(path, in, out);
		cycle = path;
		REP(i, n) if(in[i] != out[i]) cycle.clear();
		if(path.size() != 0) in[path.back()]++, out[path[0]]++; 
		REP(i, n) if(in[i] != out[i]) path.clear();
		reverse(path.begin(), path.end());
	}

	vector<int> get_path() { return path; }
	vector<int> get_cycle() { return cycle; }
};
