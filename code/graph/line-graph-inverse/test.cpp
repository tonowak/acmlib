#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<vector<int>> construct_graph(vector<pair<int, int>> ans) {
	vector<vector<int>> graph;
	for(auto [v, u] : ans) {
		int mx = max(v, u);
		if(ssize(graph) <= mx)
			graph.resize(mx + 1);
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}
	for(auto &v : graph)
		sort(v.begin(), v.end());
	return graph;
}

void test() {
	int line_n = rd(2, 6);
	int line_m = rd(0, line_n * (line_n - 1) / 2);
	set<pair<int, int>> line_edges;
	while(ssize(line_edges) < line_m) {
		int v = rd(0, line_n - 1);
		int u = rd(0, line_n - 1);
		if(v < u)
			line_edges.emplace(v, u);
	}
	debug(line_edges);

	set<vector<vector<int>>> matching_original_graphs;
	for(int og_n = 0; (matching_original_graphs.empty() and og_n <= 2 * line_n) or og_n <= 5; ++og_n) {
		vector<pair<int, int>> ans(line_n, pair(-1, -1));
		function<void (int)> backtrack = [&](int i) {
			if(i == line_n) {
				vector<int> deg(og_n);
				for(auto [v, u] : ans)
					for(int x : {v, u})
						++deg[x];
				if(*min_element(deg.begin(), deg.end()) == 0)
					return;
				matching_original_graphs.emplace(construct_graph(ans));
				return;
			}
			REP(v, og_n)
				FOR(u, v + 1, og_n - 1) {
					ans[i] = {v, u};
					auto is_valid = [&] {
						REP(j, i) {
							bool should_be_neighbor_to_v = [&] {
								return line_edges.count(pair(j, i));
							}();
							bool is_neighbor_to_v = [&] {
								auto [a, b] = ans[i];
								auto [x, y] = ans[j];
								return a == x or a == y or b == x or b == y;
							}();
							if(is_neighbor_to_v != should_be_neighbor_to_v)
								return false;
						}
						return true;
					};
					if(is_valid())
						backtrack(i + 1);
				}
		};
		backtrack(0);
	}
	debug(line_edges);
	debug(matching_original_graphs);

	vector<vector<vector<int>>> matching_big_og_graphs;
	for(auto &graph : matching_original_graphs) {
		int og_n = ssize(graph);

		auto is_connected = [&]() -> bool {
			vector<bool> visited(og_n);
			function<void (int)> dfs = [&](int v) {
				visited[v] = true;
				for(int u : graph[v])
					if(not visited[u])
						dfs(u);
			};
			dfs(0);
			return *min_element(visited.begin(), visited.end());
		};
		auto has_multiedge = [&] {
			for(auto &v : graph)
				REP(i, ssize(v) - 1)
					if(v[i] == v[i + 1])
						return true;
			return false;
		};

		if(is_connected() and og_n > 4 and not has_multiedge()) {
			debug(graph);
			matching_big_og_graphs.emplace_back(graph);
		}
	}
	debug(matching_big_og_graphs);
	for(auto &graph1 : matching_big_og_graphs) {
		auto &graph0 = matching_big_og_graphs.front();
		int og_n = ssize(graph0);
		assert(ssize(graph1) == og_n);

		auto is_matching_perm = [&] {
			vector<int> perm(og_n);
			iota(perm.begin(), perm.end(), 0);
			do {
				vector<vector<int>> transmuted1(og_n);
				REP(v, og_n)
					for(int u : graph1[v])
						transmuted1[perm[v]].emplace_back(perm[u]);
				for(auto &v : transmuted1)
					sort(v.begin(), v.end());
				if(transmuted1 == graph0)
					return true;
			} while(next_permutation(perm.begin(), perm.end()));
			return false;
		};
		assert(is_matching_perm());
	}

	auto [main_found, main_ans] = get_original_graph(line_n, vector(line_edges.begin(), line_edges.end()));
	debug(main_found, main_ans);
	auto main_graph = construct_graph(main_ans);
	debug(main_graph);

	assert(main_found == not matching_original_graphs.empty());
	if(main_found)
		assert(matching_original_graphs.count(main_graph));
}
