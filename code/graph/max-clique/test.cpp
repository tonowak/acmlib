#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 12);
	vector<bitset<max_n>> graph(n);
	int m = rd(0, n * n);
	while(m --> 0) {
		int v = rd(0, n - 1);
		int u = rd(0, n - 1);
		if(v == u)
			continue;
		graph[v][u] = graph[u][v] = true;
	}
	debug(n);
	REP(v, n)
		REP(u, n)
			debug(v, u, graph[v][u]);

	auto max_clique = get_max_clique(graph);

	auto is_ok = [&](vector<int> v) {
		REP(i, ssize(v))
			REP(j, i)
				if(not graph[v[i]][v[j]])
					return false;
		return true;
	};

	int best_brute = 0;
	REP(mask, 1 << n) {
		vector<int> v;
		REP(i, n)
			if((mask >> i) & 1)
				v.emplace_back(i);
		if(is_ok(v))
			best_brute = max(best_brute, __builtin_popcount(mask));
	}

	assert(ssize(max_clique) == best_brute);
	assert(is_ok(max_clique));
}
