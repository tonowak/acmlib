/*
 * Opis: O(n), wyznaczanie cykli w grafie. Zakłada że jest nieskierowany graf bez pętelek i multikrawędzi,
 *   każda krawędź leży na co najwyżej jednym cyklu prostym (silniejsze założenie, niż o wierzchołkach).
 *   \texttt{cactus\_cycles(graph)} zwraca taką listę cykli, że istnieje krawędź między $i$-tym, a $(i+1) \text{mod} \text{ssize(cycle)}$-tym wierzchołkiem.
 */

vector<vector<int>> cactus_cycles(vector<vector<int>> graph) {
	int n = ssize(graph);
	vector<int> state(n, 0);
	vector<int> stack;
	vector<vector<int>> ret;
	function<void (int, int)> dfs = [&](int v, int p) {
		if(state[v] == 2) {
			vector<int> cycle = {v};
			for(int i = 0; stack[ssize(stack) - 1 - i] != v; ++i)
				cycle.emplace_back(stack[ssize(stack) - 1 - i]);
			ret.emplace_back(cycle);
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
	dfs(0, -1);
	return ret;
}

