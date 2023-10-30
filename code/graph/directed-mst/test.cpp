#include <bits/stdc++.h>
using namespace std;
template<class T> auto operator<<(ostream &o, T x) -> decltype(x.end(), o);
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

ostream& operator<<(ostream &o, Edge e) {
	return o << '(' << e.a << ", " << e.b << ", " << e.w << ')';
}

bool is_correct_tree(vector<int> lit, int n, vector<Edge> edges, int root) {
	if(ssize(lit) != n - 1)
		return false;
	vector<vector<int>> graph(n);
	for(int i : lit)
		graph[edges[i].a].emplace_back(edges[i].b);
	vector<int> vis(n);
	function<void (int)> dfs = [&](int v) {
		vis[v] = true;
		for(int u : graph[v])
			if(not vis[u])
				dfs(u);
	};
	dfs(root);
	if(*min_element(vis.begin(), vis.end()) == 0)
		return false;
	return true;
}

void test() {
	int n = rd(1, 9);
	int m = rd(0, min(14, n * n));
	int max_w = rd(0, 1) ? int(1e9) : 10;
	debug(n, m, max_w);
	vector<Edge> edges(m);
	for(auto &e : edges) {
		e.a = rd(0, n - 1);
		e.b = rd(0, n - 1);
		e.w = rd(-max_w, max_w);
		debug(e.a, e.b, e.w);
	}
	int root = rd(0, n - 1);

	pair<LL, vector<int>> ans = {LL(1e18), {}};

	REP(mask, 1 << m) {
		vector<int> lit;
		REP(i, m)
			if((mask >> i) & 1)
				lit.emplace_back(i);
		if(not is_correct_tree(lit, n, edges, root))
			continue;
		LL local_ans = 0;
		for(auto i : lit)
			local_ans += edges[i].w;
		ans = min(ans, pair(local_ans, lit));
	}
	if(ans.first == LL(1e18))
		ans.first = -1;
	debug(ans);

	auto [main_ans, main_solve] = directed_mst(n, root, edges);
	debug(main_ans, main_solve);
	assert(ans.first == main_ans);
	if(ans.first != -1) {
		vector<vector<pair<int, LL>>> rev_graph(n);
		for(auto e : edges)
			rev_graph[e.b].emplace_back(e.a, e.w);
		vector<Edge> found_subset;
		LL sum = 0;
		REP(v, n)
			if(main_solve[v] != -1) {
				LL smallest_w = LL(1e18) + 1;
				for(auto [u, w] : rev_graph[v])
					if(u == main_solve[v])
						smallest_w = min(smallest_w, w);
				assert(smallest_w != LL(1e18) + 1);
				found_subset.emplace_back(main_solve[v], v, smallest_w);
				sum += smallest_w;
			}
		assert(sum == main_ans);
		vector<int> lit(ssize(found_subset));
		iota(lit.begin(), lit.end(), 0);

		assert(is_correct_tree(lit, n, found_subset, root));
	}
}
