#include "../../utils/testing/test-wrapper.cpp"
#define MCMF MCMF_spfa
#include "../mcmf-spfa/main.cpp"
#undef MCMF
#include "main.cpp"

void test() {
	const int max_n = 10;
	const int max_m = 20;
	const int max_cap = 20;
	const int max_cost = 100;
	const int n = rd(2, max_n);
	const int m = rd(0, max_m);
	vector<tuple<int, int, int, int>> edges;
	while (ssize(edges) < m) {
		int a = rd(0, n - 1);
		int b = rd(0, n - 1);
		if (a < b)
			edges.emplace_back(a, b, rd(0, max_cap), rd(-max_cost, max_cost));
	}

	MCMF mcmf(n);
	for (auto [a, b, c, d] : edges)
		mcmf.add_edge(a, b, c, d);
	auto [flow, cost] = mcmf(0, n - 1);

	MCMF_spfa mcmf_spfa(n);
	for (auto [a, b, c, d] : edges)
		mcmf_spfa.add_edge(a, b, c, d);
	auto [flow_spfa, cost_spfa] = mcmf_spfa(0, n - 1);

	assert(flow == flow_spfa);
	assert(cost == cost_spfa);
}
