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
	int n0 = rd(1, 7), n1 = rd(1, 7);
	int n = n0 + n1;
	vector<int> which_group(n0 + n1);
	REP(i, n1)
		which_group[i] = 1;
	shuffle(which_group.begin(), which_group.end(), rng);
	array<vector<int>, 2> in_group;
	REP(v, n)
		in_group[which_group[v]].emplace_back(v);

	int m = min(15, rd(0, n0 * n1 + 1));
	vector<pair<int, int>> edges(m);
	for(auto &[v, u] : edges) {
		v = in_group[0][rd(0, n0 - 1)];
		u = in_group[1][rd(0, n1 - 1)];
		if(rd(0, 1))
			swap(v, u);
	}

	vector<vector<int>> graph(n);
	for(auto [v, u] : edges) {
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}

	auto [match_size, match] = Matching(graph)();
	debug(n, edges, match_size, get_max_matching(n, edges));
	assert(match_size == get_max_matching(n, edges));
	assert(is_valid_matching(n, edges, match));
}
