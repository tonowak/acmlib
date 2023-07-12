/*
 * Opis: Wyznacza kolorowanie grafu planaranego.
 * Czas: O(n * m)
 * Użycie:
 *   coloring(graph) zwraca 5-kolorowanie grafu
 *   coloring(graph, 4) zwraca 4-kolorowanie grafu, jeżeli w każdym momencie procesu usuwania wierzchołka o najmniejszym stopniu jego stopień jest nie większy niż 4
 */

vector<int> coloring(const vector<vector<int>>& graph, const int limit = 5) {
	const int n = ssize(graph);
	if (!n) return {};
	function<vector<int>(vector<bool>)> solve = [&](const vector<bool>& active) {
		if (not *max_element(active.begin(), active.end()))
			return vector (n, -1);

		pair<int, int> best = {n, -1};
		REP(i, n) {
			if (not active[i])
				continue;
			int cnt = 0;
			for (int e : graph[i])
				cnt += active[e];
			best = min(best, {cnt, i});
		}
		const int id = best.second;
		auto cp = active;
		cp[id] = false;
		auto col = solve(cp);

		vector<bool> used(limit);
		for (int e : graph[id])
			if (active[e])
				used[col[e]] = true;
		REP(i, limit)
			if (not used[i]) {
				col[id] = i;
				return col;
			}

		for (int e0 : graph[id]) {
			for (int e1 : graph[id]) {
				if (e0 >= e1)
					continue;
				vector<bool> vis(n);
				function<void(int, int, int)> dfs = [&](int v, int c0, int c1) {
					vis[v] = true;
					for (int e : graph[v])
						if (not vis[e] and (col[e] == c0 or col[e] == c1))
							dfs(e, c0, c1);
				};
				const int c0 = col[e0], c1 = col[e1];
				dfs(e0, c0, c1);
				if (vis[e1])
					continue;
				REP(i, n)
					if (vis[i])
						col[i] = col[i] == c0 ? c1 : c0;
				col[id] = c0;
				return col;
			}
		}
		assert(false);
	};
	return solve(vector (n, true));
}
