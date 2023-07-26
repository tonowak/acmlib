/*
 * Opis: O(n), wyznaczanie cykli w grafie. Zakłada że jest nieskierowany graf bez pętelek i multikrawędzi,
 *   każda krawędź leży na co najwyżej jednym cyklu prostym (silniejsze założenie, niż o wierzchołkach).
 *   \texttt{cactus\_cycles(graph)} zwraca taką listę cykli, że istnieje krawędź między $i$-tym, a $(i+1) \text{mod} \text{ssize(cycle)}$-tym wierzchołkiem.
 */
vector<vector<int>> cactus_cycles(vector<vector<int>> graph) {
	vector<int> state(ssize(graph), 0), stack;
	vector<vector<int>> ret;
	function<void (int, int)> dfs = [&](int v, int p) {
		if(state[v] == 2) {
			ret.emplace_back(stack.rbegin(), find(stack.rbegin(), stack.rend(), v) + 1);
			return;
		}
		stack.emplace_back(v);
		state[v] = 2;
		for(int u : graph[v])
			if(u != p and state[u] != 1)
				dfs(u, v);
		state[v] = 1;
		stack.pop_back();
	};
	REP(i, ssize(graph))
		if (!state[i])
			dfs(i, -1);
	return ret;
}
