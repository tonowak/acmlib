#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool is_planar_brute(int n, vector<pair<int, int>> edges) {
	REP(mask, 1 << ssize(edges)) {
		vector<int> lead(n);
		iota(lead.begin(), lead.end(), 0);
		function<int (int)> find = [&](int v) {
			return v == lead[v] ? v : lead[v] = find(lead[v]);
		};
		REP(i, ssize(edges))
			if((mask >> i) & 1)
				lead[find(edges[i].first)] = find(edges[i].second);

		vector<int> leads;
		REP(v, n)
			if(lead[v] == v)
				leads.emplace_back(v);
		set<pair<int, int>> new_edges;
		for(auto [v, u] : edges) {
			v = find(v);
			u = find(u);
			if(v != u)
				new_edges.emplace(min(v, u), max(v, u));
		}
		debug(mask);
		debug(leads);
		debug(new_edges);

		vector<vector<int>> graph(n);
		for(auto [v, u] : new_edges) {
			graph[v].emplace_back(u);
			graph[u].emplace_back(v);
		}

		vector<bool> vis(n);
		vector<int> component;
		function<void (int)> dfs = [&](int v) {
			component.emplace_back(v);
			vis[v] = true;
			for(int u : graph[v])
				if(not vis[u])
					dfs(u);
		};

		REP(start, n)
			if(not vis[start]) {
				component.clear();
				dfs(start);

				if(ssize(component) != 5 and ssize(component) != 6)
					continue;
				int m = 0;
				for(int v : component)
					m += ssize(graph[v]);
				m /= 2;
				if(ssize(component) == 5) {
					if(m == 10)
						return false;
					continue;
				}
				if(m < 9)
					continue;
				sort(component.begin(), component.end());
				do {
					auto is_k33 = [&] {
						for(int v : {component[0], component[1], component[2]})
							for(int u : {component[3], component[4], component[5]}) {
								bool is_edge = false;
								for(auto [a, b] : new_edges)
									if(min(v, u) == min(a, b) and max(v, u) == max(a, b))
										is_edge = true;
								if(not is_edge)
									return false;
							}
						return true;
					};
					if(is_k33())
						return false;
				} while(next_permutation(component.begin(), component.end()));
			}
	}
	return true;
}

void test() {
	int n = rd(1, 15);
	int m = rd(0, min(13, n * (n - 1) / 2));
	set<pair<int, int>> edges_set;
	while(ssize(edges_set) < m) {
		int v = rd(0, n - 1);
		int u = rd(0, n - 1);
		if(v < u)
			edges_set.emplace(v, u);
	}
	debug(edges_set);

	vector<vector<int>> graph(n);
	for(auto [v, u] : edges_set) {
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}
	debug(graph);
	bool ans_main = is_planar(graph);
	debug(ans_main);
	bool ans_brut = is_planar_brute(n, vector<pair<int, int>>(edges_set.begin(), edges_set.end()));
	debug(ans_brut);
	assert(ans_main == ans_brut);
}
