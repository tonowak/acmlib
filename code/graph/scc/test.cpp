#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = 10;
	n = rd(1, n);
	int m = rd(n, n * n / 4 + 1);

	vector<vector<int>> graph(n);
	while(m --> 0)
		graph[rd(0, n - 1)].emplace_back(rd(0, n - 1));

	auto bfs = [&](int root) {
		vector<bool> reachable(n);
		reachable[root] = true;
		deque<int> que = {root};
		while(ssize(que)) {
			int v = que.front();
			que.pop_front();
			for(int u : graph[v])
				if(not reachable[u]) {
					reachable[u] = true;
					que.emplace_back(u);
				}
		}
		return reachable;
	};

	vector<vector<bool>> reachable(n);
	REP(v, n)
		reachable[v] = bfs(v);

	SCC scc(graph);
	debug(graph, scc.group);
	REP(v, n)
		REP(u, n)
			if(reachable[v][u] && reachable[u][v])
				assert(scc.group[v] == scc.group[u]);
			else
				assert(scc.group[v] != scc.group[u]);
}
