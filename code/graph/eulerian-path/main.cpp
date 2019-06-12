// Ścieżka Eulera
// Status : Nieprzetestowany
// Eulerian_Path(m, graph()).get() zwraca ścieżkę
// lub pusty vector jeśli ścieżka nie istnieje

struct Eulerian_Path
{
	vector<vector<pair<int, int>>> graph; // {dest, id}
	vector<bool> used;
	vector<int> path, in, out;

	void init(int v = 0)
	{
		in[v]++;
		while(!graph[v].empty())
		{
			auto edge = graph[v].back();
			graph[v].pop_back();
			int u = edge.first;
			int id = edge.second;
			if(used[id]) continue;
			used[id] = true;
			out[v]++;
			init(u);
		}
		path.emplace_back(v);
	}

	Eulerian_Path(int m, vector<vector<pair<int, int>>> graph) : graph(graph)
	{
		int n = size(graph);
		used.resize(m);
		in.resize(n);
		out.resize(n);

		init();
		in[0]--;
		debug(path, in, out);
		// delete next line to get only cycles
		if(path.size() != 0) in[path.back()]++, out[path[0]]++; 
		REP(i, n) if(in[i] != out[i]) path.clear();
		reverse(path.begin(), path.end());
	}

	vector<int> get() { return path; }
};
