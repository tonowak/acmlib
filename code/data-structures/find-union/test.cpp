#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 10);
	vector<vector<int>> graph(n);
	auto get_colors = [&] {
		vector<int> color(n, -1);
		int last_c = 0;
		REP(v, n)
			if(color[v] == -1) {
				function<void (int)> dfs = [&](int u) {
					color[u] = last_c;
					for(int w : graph[u])
						if(color[w] == -1)
							dfs(w);
				};
				dfs(v);
				++last_c;
			}
		return pair(color, last_c);
	};
	FindUnion fu(n);
	REP(edge, 2 * n) {
		int v = rd(0, n - 1);
		int u = rd(0, n - 1);
		if(v == u)
			continue;
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
		fu.join(v, u);

		auto [colors, color_cnt] = get_colors();
		REP(a, n)
			REP(b, n)
				assert((colors[a] == colors[b]) == (fu.same_set(a, b)));
		REP(a, n)
			if(fu.find(a) == a) {
				int sz = 0;
				REP(b, n)
					if(colors[a] == colors[b])
						++sz;
				assert(sz == fu.size(a));
			}
	}
}
