#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	const int max_n = 20;
	const int max_cap = 20;
	const int n = rd(2, max_n);
	const int iters = rd(0, 50);

	vector graph(n, vector (n, 0));
	Dinic dinic(n);

	auto rd_vertex = [&] {
		return rd(0, n - 1);
	};

	int source = rd_vertex();
	int sink = source;
	while (sink == source)
		sink = rd_vertex();

	REP(iter, iters) {
		int a = rd_vertex();
		int b = rd_vertex();
		int c = rd(0, max_cap);
		graph[a][b] += c;
		dinic.add_edge(a, b, c);
	}
	auto flow = dinic(source, sink);
	auto flowing = dinic.get_flowing();
	debug(graph);
	debug(flow, flowing);

	vector<int> sum(n);
	for (auto [edge, c] : flowing) {
		auto [a, b] = edge;
		sum[a] += c;
		sum[b] -= c;
		assert(c >= 0 and c <= graph[a][b]);
	}
	REP(i, n) {
		if (i == source)
			assert(sum[i] == flow);
		else if (i == sink)
			assert(sum[i] == -flow);
		else
			assert(sum[i] == 0);
	}
	vector<bool> vis(n);
	function<void(int)> dfs = [&](int v) {
		assert(v != sink);
		debug(v);
		vis[v] = true;
		REP(i, n)
			if (not vis[i] and flowing[pair(v, i)] < graph[v][i])
				dfs(i);
	};
	dfs(source);
}
