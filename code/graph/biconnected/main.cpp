
/*
 * Opis: Dwuspójne składowe, mosty oraz punkty artykulacji.
 * Czas: O(n + m)
 * Użycie: po skonstruowaniu, bicon = zbiór list id krawędzi, bridges = lista id krawędzi będącymi mostami, arti_points = lista wierzchołków będącymi punktami artykulacji. Tablice są nieposortowane. Wspiera multikrawędzie i wiele spójnych, ale nie pętelki.
 */

struct Low {
	vector<vector<int>> graph;
	vector<int> low, pre;
	vector<pair<int, int>> edges;

	vector<vector<int>> bicon;
	vector<int> bicon_stack, arti_points, bridges;
	int gtime = 0;

	void dfs(int v, int p) {
		low[v] = pre[v] = gtime++;
		bool considered_parent = false;
		int son_count = 0;
		bool is_arti = false;

		for(int e : graph[v]) {
			int u = edges[e].first ^ edges[e].second ^ v;
			if(u == p and not considered_parent)
				considered_parent = true;
			else if(pre[u] == -1) {
				bicon_stack.emplace_back(e);
				dfs(u, v);
				low[v] = min(low[v], low[u]);

				if(low[u] >= pre[v]) {
					bicon.emplace_back();
					do {
						bicon.back().emplace_back(bicon_stack.back());
						bicon_stack.pop_back();
					} while(bicon.back().back() != e);
				}

				++son_count;
				if(p != -1 and low[u] >= pre[v])
					is_arti = true;

				if(low[u] > pre[v])
					bridges.emplace_back(e);
			}
			else if(pre[v] > pre[u]) {
				low[v] = min(low[v], pre[u]);
				bicon_stack.emplace_back(e);
			}
		}

		if(p == -1 and son_count > 1)
			is_arti = true;
		if(is_arti)
			arti_points.emplace_back(v);
	}

	Low(int n, vector<pair<int, int>> _edges) : graph(n), low(n), pre(n, -1), edges(_edges) {
		REP(i, ssize(edges)) {
			auto [v, u] = edges[i];
#ifdef LOCAL
			assert(v != u);
#endif
			graph[v].emplace_back(i);
			graph[u].emplace_back(i);
		}
		REP(v, n)
			if(pre[v] == -1)
				dfs(v, -1);
	}
};
