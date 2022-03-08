#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	int m = rd(0, n * n);
	vector<vector<pair<int, int>>> graph(n);
	while(m --> 0)
		graph[rd(0, n - 1)].emplace_back(rd(0, n - 1), rd(-2 * n, 2 * n));
	debug(graph);

	auto [is_cycle, cycle] = negative_cycle(graph);
	debug(is_cycle, cycle);

	auto is_cycle_floyd_warshall = [&] {
		constexpr int inf = int(1e9);
		vector dist(n, vector<int>(n, inf));
		REP(v, n)
			dist[v][v] = 0;
		REP(v, n)
			for(auto [u, w] : graph[v])
				dist[v][u] = min(dist[v][u], w);
		REP(k, n)
			REP(i, n)
				REP(j, n) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
					dist[i][j] = max(dist[i][j], -inf);
				}
		REP(v, n)
			if(dist[v][v] < 0)
				return true;
		return false;
	};
	assert(is_cycle == is_cycle_floyd_warshall());
	if(not is_cycle)
		return;

	int sum_on_cycle = 0;
	REP(i, ssize(cycle)) {
		int v = cycle[i];
		int u = cycle[(i + 1) % ssize(cycle)];
		bool found = false;
		int found_w;
		for(auto [uu, w] : graph[v])
			if(uu == u) {
				if(not found) {
					found_w = w;
					found = true;
				}
				else
					found_w = min(found_w, w);
			}
		assert(found);
		sum_on_cycle += found_w;
	}
	assert(sum_on_cycle < 0);

	sort(cycle.begin(), cycle.end());
	REP(i, ssize(cycle) - 1)
		assert(cycle[i] != cycle[i + 1]);
}
