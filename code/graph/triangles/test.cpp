#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = 10;
	n = rd(2, n);
	int m = min(19, rd(0, n * n));
	set<pair<int, int>> used;
	vector<pair<int, int>> edges;
	while(m --> 0) {
		int v = rd(0, n - 1);
		int u = rd(0, n - 1);
		while(v == u)
			u = rd(0, n - 1);
		if(v > u)
			swap(v, u);
		if(used.find(pair(v, u)) != used.end())
			continue;
		edges.emplace_back(v, u);
		used.emplace(v, u);
	}
	debug(n, edges);

	int triangles3 = 0, paths3 = 0, stars3 = 0;
	int ps4 = 0, rectangles4 = 0, ys4 = 0, paths4 = 0, stars4 = 0;

	REP(mask, 1 << ssize(edges)) {
		int popcount = __builtin_popcount(mask);
		if(popcount != 3 and popcount != 4)
			continue;

		vector<vector<int>> graph(n);
		REP(i, ssize(edges))
			if((mask >> i) & 1) {
				auto [v, u] = edges[i];
				graph[v].emplace_back(u);
				graph[u].emplace_back(v);
			}
		vector<int> new_id(n, -1);
		int new_n = 0;
		REP(v, n)
			if(ssize(graph[v]))
				new_id[v] = new_n++;

		vector<vector<int>> new_graph(new_n);
		REP(v, n)
			for(int u : graph[v])
				if(new_id[v] != -1 and new_id[u] != -1)
					new_graph[new_id[v]].emplace_back(new_id[u]);
		debug(new_graph, popcount, new_n);

		vector<int> deg(new_n);
		REP(i, new_n)
			deg[i] = ssize(new_graph[i]);
		sort(deg.begin(), deg.end());
		// debug(deg);

		vector<bool> vis(new_n);
		function<void (int)> dfs = [&](int v) {
			vis[v] = true;
			for(int u : new_graph[v])
				if(not vis[u])
					dfs(u);
		};
		dfs(0);
		if(*min_element(vis.begin(), vis.end()) == false)
			continue;

		auto get = [&]() -> int& {
			if(popcount == 3) {
				if(deg[0] == 2)
					return triangles3;
				else if(deg.back() == 3)
					return stars3;
				return paths3;
			}
			if(deg[0] == 2)
				return rectangles4;
			if(deg.back() == 4)
				return stars4;
			if(new_n == 4) {
				assert(deg[0] == 1 and deg[1] == 2 and deg[2] == 2 and deg[3] == 3);
				return ps4;
			}
			if(new_n == 5 and deg.back() == 3) {
				assert(deg[0] == 1 and deg[1] == 1 and deg[2] == 1 and deg[3] == 2 and deg[4] == 3);
				return ys4;
			}
			if(new_n == 5) {
				assert(deg[0] == 1 and deg[1] == 1 and deg[2] == 2 and deg[3] == 2 and deg[4] == 2);
				debug("4", mask, deg);
				return paths4;
			}
			assert(false);
		};
		get() += 1;
	}

	vector<vector<int>> all_graph(n);
	for(auto [v, u] : edges) {
		all_graph[v].emplace_back(u);
		all_graph[u].emplace_back(v);
	}

	Triangles t(all_graph);
	debug(triangles3, t.triangles3);
	assert(triangles3 == t.triangles3);
	debug(paths3, t.paths3);
	assert(paths3 == t.paths3);
	debug(ps4, t.ps4);
	assert(ps4 == t.ps4);
	debug(rectangles4, t.rectangles4);
	assert(rectangles4 == t.rectangles4);
	debug(ys4, t.ys4);
	assert(ys4 == t.ys4);
	debug(paths4, t.paths4);
	assert(paths4 == t.paths4);
	debug(stars4, t.stars4);
	assert(stars4 == t.stars4);
}
