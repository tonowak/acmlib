#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

int components_cnt(int n, vector<pair<int, int>> edges, bool ignore_alone = false) {
	vector<vector<int>> graph(n);
	for(auto [v, u] : edges) {
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}
	vector<bool> visited(n);
	function<void (int)> dfs = [&](int v) {
		visited[v] = true;
		for(int u : graph[v])
			if(not visited[u])
				dfs(u);
	};
	int ans = 0;
	REP(v, n)
		if(not visited[v] and (not ignore_alone or ssize(graph[v]))) {
			++ans;
			dfs(v);
		}
	return ans;
}

bool is_cycle(int n, vector<pair<int, int>> edges) {
	if(components_cnt(n, edges, true) != 1)
		return false;
	vector<int> deg(n);
	for(auto [v, u] : edges) {
		++deg[v];
		++deg[u];
	}
	REP(v, n)
		if(deg[v] != 2 and deg[v] != 0)
			return false;
	return true;
}

bool is_bicon(int n, vector<pair<int, int>> edges) {
	if(components_cnt(n, edges, true) != 1)
		return false;
	vector both_through_cycle(ssize(edges), vector<bool>(ssize(edges)));
	REP(subset_cycle, 1 << ssize(edges)) {
		vector<pair<int, int>> cycle;
		vector<int> idx;
		REP(i, ssize(edges))
			if((subset_cycle >> i) & 1) {
				cycle.emplace_back(edges[i]);
				idx.emplace_back(i);
			}
		if(not is_cycle(n, cycle))
			continue;

		for(int i : idx)
			for(int j : idx)
				both_through_cycle[i][j] = both_through_cycle[j][i] = true;
	}
	bool valid = true;
	for(auto &v : both_through_cycle)
		for(bool b : v)
			if(not b)
				valid = false;
	return valid or ssize(edges) == 1;
}

vector<vector<int>> bicons(int n, vector<pair<int, int>> edges) {
	vector<int> remaining_edges_id(ssize(edges));
	iota(remaining_edges_id.begin(), remaining_edges_id.end(), 0);
	vector<vector<int>> ret;

	while(not remaining_edges_id.empty()) {
		pair<int, int> biggest_bicon = {-1, -1};
		REP(mask, 1 << ssize(remaining_edges_id)) {
			vector<pair<int, int>> sub_edges;
			REP(i, ssize(remaining_edges_id))
				if((mask >> i) & 1)
					sub_edges.emplace_back(edges[remaining_edges_id[i]]);
			if(is_bicon(n, sub_edges))
				biggest_bicon = max(biggest_bicon, pair(ssize(sub_edges), mask));
		}
		assert(biggest_bicon.first > 0);
		ret.emplace_back();
		vector<int> remaining;
		REP(i, ssize(remaining_edges_id))
			if((biggest_bicon.second >> i) & 1)
				ret.back().emplace_back(remaining_edges_id[i]);
			else
				remaining.emplace_back(remaining_edges_id[i]);
		remaining_edges_id = remaining;
	}
	return ret;
}

vector<int> arti_points(int n, vector<pair<int, int>> edges) {
	int init_cnt = components_cnt(n, edges);
	vector<int> ret;
	REP(deleted, n) {
		vector<pair<int, int>> sub_edges;
		int cnt_edges_deleted = 0;
		for(auto [v, u] : edges)
			if(v != deleted and u != deleted)
				sub_edges.emplace_back(v, u);
			else
				++cnt_edges_deleted;
		if(cnt_edges_deleted == 0) {
			// izolowany
			continue;
		}
		debug(deleted, components_cnt(n, sub_edges));
		if(components_cnt(n, sub_edges) - 1 != init_cnt)
			ret.emplace_back(deleted);
	}
	return ret;
}

vector<int> bridges(int n, vector<pair<int, int>> edges) {
	int init_cnt = components_cnt(n, edges);
	vector<int> ret;
	REP(deleted, ssize(edges)) {
		auto sub_edges = edges;
		sub_edges.erase(sub_edges.begin() + deleted);
		if(components_cnt(n, sub_edges) != init_cnt)
			ret.emplace_back(deleted);
	}
	return ret;
}

void test() {
	int n = rd(2, 8);
	int m = rd(0, 9);
	vector<pair<int, int>> edges(m);
	for(auto &[v, u] : edges) {
		v = rd(0, n - 1);
		u = rd(0, n - 1);
		while(v == u)
			u = rd(0, n - 1);
	}
	debug(edges);

	auto low = Low(n, edges);
	auto brute_bicon = bicons(n, edges);
	auto main_bicon = low.bicon;
	debug(brute_bicon);
	debug(main_bicon);
	for(auto &v : brute_bicon)
		sort(v.begin(), v.end());
	for(auto &v : main_bicon)
		sort(v.begin(), v.end());
	sort(brute_bicon.begin(), brute_bicon.end());
	sort(main_bicon.begin(), main_bicon.end());
	assert(brute_bicon == main_bicon);

	auto brute_arti = arti_points(n, edges);
	auto main_arti = low.arti_points;
	debug(brute_arti, main_arti);
	sort(main_arti.begin(), main_arti.end());
	assert(brute_arti == main_arti);

	auto brute_bridges = bridges(n, edges);
	auto main_bridges = low.bridges;
	sort(main_bridges.begin(), main_bridges.end());
	assert(brute_bridges == main_bridges);
}
