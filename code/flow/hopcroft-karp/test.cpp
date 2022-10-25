#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
#include "../matching/main.cpp"

void test() {
	int n0 = rd(1, 10);
	int n1 = rd(1, 10);
	vector<vector<int>> graph(n0 + n1);
	int m = rd(1, 100);
	while(m --> 0) {
		int v = rd(0, n0 - 1);
		int u = rd(n0, n0 + n1 - 1);
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}
	auto [ans, match] = hopcroft_karp(graph, n0, n1);
	vector<bool> vis(n0 + n1);
	int ans_check = 0;
	REP(v, n0)
		assert(match[v] == -1 or match[v] >= n0);
	FOR(v, n0, n0 + n1 - 1)
		assert(match[v] == -1 or match[v] < n0);
	debug(match);
	REP(v, n0)
		if(match[v] != -1)
			assert(match[match[v]] == v);
	for(int u : match)
		if(u != -1) {
			assert(not vis[u]);
			vis[u] = true;
			++ans_check;
		}
	assert(ans == ans_check / 2);
	assert(ans == Matching(graph)().first);
}
