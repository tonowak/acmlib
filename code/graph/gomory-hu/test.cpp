#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 10), m = rd(0, n * n);
	vector<tuple<int, int, int>> edges(m);
	for(auto &[v, u, cap] : edges) {
		v = rd(0, n - 1);
		u = rd(0, n - 1);
		cap = rd(0, 10);
	}
	vector gomory_hu = get_gomory_hu(n, edges);
	REP(s, n)
		REP(t, n) {
			if(s == t)
				continue;
			Dinic dinic(n);
			for(auto [v, u, cap] : edges) {
				dinic.add_edge(v, u, cap);
				dinic.add_edge(u, v, cap);
			}
			int got = dinic(s, t);
			debug(s, t, got, gomory_hu[s][t]);
			assert(got == gomory_hu[s][t]);
		}
}
