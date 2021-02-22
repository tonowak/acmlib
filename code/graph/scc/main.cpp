/*
 * Opis: Silnie Spójnie Składowe
 * Czas: O(\log n)
 * Użycie:
 *   kontruktor - SCC(graph)
 *   group[v] to numer silnie spójnej wierzchołka v
 *   get_compressed() zwraca graf siline spójnych
 *   get_compressed(false) nie usuwa multikrawędzi
 */

struct SCC {
	int n;
	vector<vector<int>> &graph;
	int group_cnt = 0;
	vector<int> group;


	vector<vector<int>> rev_graph;
	vector<int> order;

	void order_dfs(int v) {
		group[v] = 1;
		for(int u : rev_graph[v])
			if(group[u] == 0)
				order_dfs(u);
		order.emplace_back(v);
	}

	void group_dfs(int v, int color) {
		group[v] = color;
		for(int u : graph[v])
			if(group[u] == -1)
				group_dfs(u, color);
	}

	SCC(vector<vector<int>> &_graph) : graph(_graph) {
		n = ssize(graph);
		rev_graph.resize(n);
		REP(v, n)
			for(int u : graph[v])
				rev_graph[u].emplace_back(v);

		group.resize(n);
		REP(v, n)
			if(group[v] == 0)
				order_dfs(v);
		reverse(order.begin(), order.end());
		debug(order);

		group.assign(n, -1);
		for(int v : order)
			if(group[v] == -1)
				group_dfs(v, group_cnt++);
	}

	vector<vector<int>> get_compressed(bool delete_same = true) {
		vector<vector<int>> ans(group_cnt);
		REP(v, n)
			for(int u : graph[v])
				if(group[v] != group[u])
					ans[group[v]].emplace_back(group[u]);

		if(not delete_same)
			return ans;
		REP(v, group_cnt) {
			sort(ans[v].begin(), ans[v].end());
			ans[v].erase(unique(ans[v].begin(), ans[v].end()), ans[v].end());
		}
		return ans;
	}
};
