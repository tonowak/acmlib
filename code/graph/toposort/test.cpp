#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool is_permutation(vector<int> t) {
	int n = ssize(t);
	vector<int> odw(n);
	REP (i, n) {
		if (t[i] < 0 || n <= t[i])
			return false;
		if (odw[t[i]])
			return false;
		odw[t[i]] = 1;
	}
	return true;
}

void test() {
	int n = rd(0, 100);
	int m = rd(0, 400);
	if (n < 2)
		m = 0;
	vector<vector<int>> graph(n);
	vector<int> per(n);
	iota(per.begin(), per.end(), 0);
	shuffle(per.begin(), per.end(), tester_rng);
	REP (i, m) {
		int u = rd(0, n - 2);
		int v = rd(u + 1, n - 1);
		graph[per[u]].emplace_back(per[v]);
	}

	// check get_toposort_order
	auto ord = get_toposort_order(graph);
	assert(ssize(ord) == n);
	assert(is_permutation(ord));
	vector<int> odw(n);
	REP (i, n) {
		odw[ord[i]] = 1;
		for (int j : graph[ord[i]])
			assert(!odw[j]);
	}
	
	// check get_new_vertex_id_from_order
	auto id = get_new_vertex_id_from_order(ord);
	assert(ssize(id) == n);
	assert(is_permutation(id));
	REP (i, n)
		assert(ord[id[i]] == i);

	// check permute
	struct info {
		LL a;
		int b;
	};
	vector<info> info_tab(n);
	REP (i, n) {
		info_tab[i].a = (LL)rd(1, int(1e9)) * rd(1, int(1e9));
		info_tab[i].b = rd(1, 100);
	}
	auto reordered_tab = permute(info_tab, id);
	assert(ssize(reordered_tab) == n);
	REP (i, n) {
		assert(info_tab[ord[i]].a == reordered_tab[i].a);
		assert(info_tab[ord[i]].b == reordered_tab[i].b);
	}

	// check renumerate_vertices
	auto ren_graph = renumerate_vertices(graph, id);
	assert(ssize(ren_graph) == n);
	multiset<pair<int, int>> original, renumerated;
	REP (i, n) {
		for (int j : graph[i])
			original.emplace(id[i], id[j]);
		for (int j : ren_graph[i])
			renumerated.emplace(i, j);
	}
	assert(original == renumerated);
}
