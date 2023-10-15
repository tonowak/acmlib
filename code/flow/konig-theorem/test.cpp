#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

template<typename T>
bool contains(const vector<T>& v, T x) {
	return find(v.begin(), v.end(), x) != v.end();
}

bool is_edge_coverable(int n, const vector<pair<int, int>>& edges) {
	vector<int> vis(n, 1);
	for (auto [a, b] : edges)
		vis[a] = vis[b] = 0;
	return n == 0 or *max_element(vis.begin(), vis.end()) == 0;
}

bool is_edge_cover(int n, const vector<pair<int, int>>& edges, const vector<pair<int, int>>& edge_cover) {
	auto doubled_edges = edges;
	for (auto [a, b] : edges)
		doubled_edges.emplace_back(b, a);
	for (auto e : edge_cover)
		if (not contains(doubled_edges, e))
			return false;

	vector<int> vis(n, 1);
	for (auto [a, b] : edge_cover)
		vis[a] = vis[b] = 0;
	return n == 0 or *max_element(vis.begin(), vis.end()) == 0;
}

int brute_edge_cover(int n, const vector<pair<int, int>>& edges) {
	int ans = ssize(edges);
	REP(mask, 1 << ssize(edges)) {
		vector<pair<int, int>> edge_cover;
		REP(i, ssize(edges))
			if ((mask >> i) & 1)
				edge_cover.emplace_back(edges[i]);
		if (is_edge_cover(n, edges, edge_cover))
			ans = min(ans, __builtin_popcount(mask));
	}
	return ans;
}

bool is_independent_set(int n, const vector<pair<int, int>>& edges, const vector<int> independent_set) {
	assert(independent_set.empty() or *min_element(independent_set.begin(), independent_set.end()) >= 0);
	assert(independent_set.empty() or *max_element(independent_set.begin(), independent_set.end()) < n);
	for (auto [a, b] : edges)
		if (contains(independent_set, a) and contains(independent_set, b))
			return false;
	return true;
}

int brute_independent_set(int n, const vector<pair<int, int>>& edges) {
	int ans = 0;
	REP(mask, 1 << n) {
		vector<int> independent_set;
		REP(i, n)
			if ((mask >> i) & 1)
				independent_set.emplace_back(i);
		if (is_independent_set(n, edges, independent_set))
			ans = max(ans, __builtin_popcount(mask));
	}
	return ans;
}

bool is_vertex_cover(int n, const vector<pair<int, int>>& edges, const vector<int> vertex_cover) {
	assert(vertex_cover.empty() or *min_element(vertex_cover.begin(), vertex_cover.end()) >= 0);
	assert(vertex_cover.empty() or *max_element(vertex_cover.begin(), vertex_cover.end()) < n);
	for (auto [a, b] : edges)
		if (not contains(vertex_cover, a) and not contains(vertex_cover, b))
			return false;
	return true;
}

int brute_vertex_cover(int n, const vector<pair<int, int>>& edges) {
	int ans = ssize(edges);
	REP(mask, 1 << n) {
		vector<int> vertex_cover;
		REP(i, n)
			if ((mask >> i) & 1)
				vertex_cover.emplace_back(i);
		if (is_vertex_cover(n, edges, vertex_cover))
			ans = min(ans, __builtin_popcount(mask));
	}
	return ans;
}

void test() {
	const int max_side = 7;
	const int max_edges = 15;

	int n0 = rd(0, max_side), n1 = rd(0, max_side);
	int n = n0 + n1;
	vector<int> which_group(n0 + n1);
	REP(i, n1)
		which_group[i] = 1;
	shuffle(which_group.begin(), which_group.end(), rng);
	array<vector<int>, 2> in_group;
	REP(v, n)
		in_group[which_group[v]].emplace_back(v);

	int m = min(max_edges, rd(0, n0 * n1));
	vector<pair<int, int>> edges(m);
	for(auto &[v, u] : edges) {
		v = in_group[0][rd(0, n0 - 1)];
		u = in_group[1][rd(0, n1 - 1)];
		if(rd(0, 1))
			swap(v, u);
	}
	debug(n, edges);

	vector<vector<int>> graph(n);
	for(auto [v, u] : edges) {
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}

	{ // min_edge_cover
		auto edge_cover = get_min_edge_cover(graph);
		debug(edge_cover);
		if (is_edge_coverable(n, edges)) {
			assert(ssize(edge_cover) == brute_edge_cover(n, edges));
			assert(is_edge_cover(n, edges, edge_cover));
		}
	}

	{ // max_independent_set
		auto independent_set = get_max_independent_set(graph);
		debug(independent_set);
		assert(ssize(independent_set) == brute_independent_set(n, edges));
		assert(is_independent_set(n, edges, independent_set));
	}

	{ // min_vertex_cover
		auto vertex_cover = get_min_vertex_cover(graph);
		debug(vertex_cover);
		assert(ssize(vertex_cover) == brute_vertex_cover(n, edges));
		assert(is_vertex_cover(n, edges, vertex_cover));
	}
}
