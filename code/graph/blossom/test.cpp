#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

int get_max_matching(int n, vector<pair<int, int>> edges) {
	int answer = 0;
	REP(mask, 1 << ssize(edges)) {
		bool is_valid = true;
		vector<bool> is_taken(n, false);
		REP(i, ssize(edges))
			if((mask >> i) & 1) {
				auto [v, u] = edges[i];
				if(is_taken[v] or is_taken[u]) {
					is_valid = false;
					break;
				}
				is_taken[v] = is_taken[u] = true;
			}
		if(is_valid)
			answer = max(answer, __builtin_popcount(mask));
	}
	return answer;
}

bool is_valid_matching(int n, vector<pair<int, int>> edges, vector<int> match) {
	REP(v, n)
		if(match[v] != -1) {
			bool found = false;
			for(auto [x, y] : edges)
				if(min(x, y) == min(v, match[v]) and max(x, y) == max(v, match[v])) {
					found = true;
					break;
				}
			if(not found)
				return false;
		}
	return true;
}

void test() {
	int n = rd(2, 14);
	int m = min(15, rd(0, n * n));
	vector<pair<int, int>> edges(m);
	for(auto &[v, u] : edges) {
		while(true) {
			v = rd(0, n - 1);
			u = rd(0, n - 1);
			if(v != u)
				break;
		}
	}

	vector<vector<int>> graph(n);
	for(auto [v, u] : edges) {
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}

	vector match = blossom(graph);
	int match_size = 0;
	for(int x : match)
		match_size += bool(x != -1);
	match_size /= 2;
	debug(n, edges, match_size, get_max_matching(n, edges));
	assert(match_size == get_max_matching(n, edges));
	assert(is_valid_matching(n, edges, match));
}
