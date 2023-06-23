#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = 1;
	vector<pair<int, int>> all_edges, cycle_edges;

	auto add_edge = [&](int a, int b) {
		all_edges.emplace_back(a, b);
		all_edges.emplace_back(b, a);
	};
	auto add_cycle_edge = [&](int a, int b) {
		add_edge(a, b);
		cycle_edges.emplace_back(a, b);
		cycle_edges.emplace_back(b, a);
	};

	auto add_bridge = [&] {
		int x = rd(0, n - 1);
		add_edge(x, n);
		++n;
	};
	auto add_cycle = [&] {
		int len = rd(3, 10);
		int x = rd(0, n - 1);
		REP(i, len - 2)
			add_cycle_edge(n + i, n + 1 + i);
		add_cycle_edge(x, n);
		add_cycle_edge(x, n + len - 2);
		n += len - 1;
	};
	auto add_vertex = [&] {
		++n;
	};

	int mn = rd(1, 30);
	while (n < mn) {
		if (rd(0, 2) == 0)
			add_bridge();
		else if (rd(0, 1))
			add_cycle();
		else
			add_vertex();
	}

	vector<vector<int>> graph(n);
	for (auto [a, b] : all_edges)
		graph[a].emplace_back(b);
	debug(graph);

	auto cycles = cactus_cycles(graph);
	auto test_edge = [&](int a, int b) {
		auto it = find(cycle_edges.begin(), cycle_edges.end(), pair(a, b));
		assert(it != cycle_edges.end());
		cycle_edges.erase(it);
	};
	for (auto v : cycles) {
		REP(i, ssize(v)) {
			int a = v[i], b = v[(i + 1) % ssize(v)];
			test_edge(a, b);
			test_edge(b, a);
		}
	}
	assert(cycle_edges.empty());
}
