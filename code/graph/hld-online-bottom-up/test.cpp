#include "../../utils/testing/test-wrapper.cpp"

constexpr int mod = 998'244'353;
int add(int a, int b) {
	a += b;
	return a >= mod ? a - mod : a;
}
int mul(int a, int b) {
	return int((LL(a) * b) % mod);
}

using Value_v = int;
struct DpTwoEnds {
	Value_v color_u = -1, color_d = -1;
	int ways_total = 0, ways_u = 0, ways_d = 0, ways_ud = 0;
};
DpTwoEnds merge(DpTwoEnds u, DpTwoEnds d) {
	DpTwoEnds ret;
	ret.color_u = u.color_u;
	ret.color_d = d.color_d;
	ret.ways_total = add(d.ways_total, u.ways_total);
	ret.ways_u = u.ways_u;
	ret.ways_d = d.ways_d;
	if(d.color_u == u.color_d) {
		ret.ways_total = add(ret.ways_total, mul(u.ways_d, d.ways_u));
		ret.ways_u = add(ret.ways_u, mul(u.ways_ud, d.ways_u));
		ret.ways_d = add(ret.ways_d, mul(d.ways_ud, u.ways_d));
		ret.ways_ud = mul(d.ways_ud, u.ways_ud);
	}
	return ret;
}
struct DpOneEnd {
	int ways_without_parent = 0, ways_with_parent_0 = 1, ways_with_parent_1 = 1;
};
DpOneEnd merge(DpOneEnd a, DpOneEnd b) {
	return DpOneEnd {
		.ways_without_parent = add(a.ways_without_parent, b.ways_without_parent),
		.ways_with_parent_0 = mul(a.ways_with_parent_0, b.ways_with_parent_0),
		.ways_with_parent_1 = mul(a.ways_with_parent_1, b.ways_with_parent_1)
	};
}
DpTwoEnds merge(DpOneEnd sons, Value_v value_parent) {
	int ways_including_vertex = value_parent == 0 ? sons.ways_with_parent_0 : sons.ways_with_parent_1;
	return DpTwoEnds {
		.color_u = value_parent,
		.color_d = value_parent,
		.ways_total = add(sons.ways_without_parent, ways_including_vertex),
		.ways_u = ways_including_vertex,
		.ways_d = ways_including_vertex,
		.ways_ud = ways_including_vertex,
	};
}
DpOneEnd two_to_one(DpTwoEnds two) {
	return DpOneEnd {
		.ways_without_parent = two.ways_total,
		.ways_with_parent_0 = add(1, two.color_u == 0 ? two.ways_u : 0),
		.ways_with_parent_1 = add(1, two.color_u == 1 ? two.ways_u : 0)
	};
}

#include "main.cpp"

void test() {
	int n = rd(1, 12);
	vector<vector<int>> graph(n);
	FOR(v, 1, n - 1) {
		int u = rd(0, v - 1);
		graph[v].emplace_back(u);
		graph[u].emplace_back(v);
	}

	vector<int> color(n);
	REP(i, n)
		color[i] = rd(0, 1);

	auto get_brute = [&] {
		int ans = 0;
		REP(mask, 1 << n)
			if(mask != 0) {
				vector<bool> vis(n);
				function<void (int)> dfs = [&](int v) {
					vis[v] = true;
					for(int u : graph[v])
						if(not vis[u] and ((mask >> u) & 1))
							dfs(u);
				};
				REP(v, n)
					if((mask >> v) & 1) {
						dfs(v);
						break;
					}
				if(accumulate(vis.begin(), vis.end(), 0) != __builtin_popcount(mask))
					continue;
				vector<int> colors;
				REP(v, n)
					if(vis[v])
						colors.emplace_back(color[v]);
				if(*min_element(colors.begin(), colors.end()) == *max_element(colors.begin(), colors.end()))
					++ans;
			}
		return ans;
	};

	DpDynamicBottomUp dp(graph, color);

	int iter = rd(1, 20);
	while(iter --> 0) {
		assert(dp.get().ways_total == get_brute());
		int v = rd(0, n - 1);
		color[v] = rd(0, 1);
		dp.set(v, color[v]);
	}
}
