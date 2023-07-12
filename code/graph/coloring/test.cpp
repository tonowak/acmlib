#include "../../utils/testing/test-wrapper.cpp"
#include "../../geo/intersect-lines/main.cpp"
#include "main.cpp"

const int max_z = 1000;
const int INF = 10 * max_z;
int rd_coord() {
	return rd(-max_z, max_z);
};
P rd_point() {
	return P(rd_coord(), rd_coord());
};
vector<P> gen_noncollinear_points(int n) {
	if (n == 0)
		return {};
	if (n == 3)
		return {P(-INF, 0), P(INF, INF), P(INF, -INF)};
	auto ret = gen_noncollinear_points(n - 1);
	while (true) {
		auto new_point = rd_point();
		bool ok = true;
		REP(i, ssize(ret)) {
			REP(j, i) {
				if (dir(ret[i], ret[j], new_point) == 0) {
					ok = false;
					break;
				}
			}
		}
		if (ok) {
			ret.emplace_back(new_point);
			return ret;
		}
	}
};

void test() {
	auto max_number_of_edges = [](int n) {
		if (n <= 1)
			return 0;
		if (n == 2)
			return 1;
		return 3 * n - 6;
	};

	const int max_n = 20;
	const int n = rd(0, max_n);
	const int limit = n < 12 and rd(0, 1) ? 4 : 5;
	const int m = rd(0, max_number_of_edges(n));

	const auto points = gen_noncollinear_points(n);
	debug(points);

	vector<vector<int>> graph(n);
	set<pair<int, int>> edges;
	REP(i, m) {
		while (true) {
			int a = rd(0, n - 1);
			int b = rd(0, n - 1);
			if (a == b)
				continue;
			if (edges.find(pair(a, b)) != edges.end())
				continue;

			bool ok = true;
			for (auto [c, d] : edges) {
				if (c == a or c == b or d == a or d == b)
					continue;
				if (is_intersection_segment(points[a], points[b], points[c], points[d])) {
					ok = false;
					break;
				}
			}
			if (not ok)
				continue;

			edges.emplace(a, b);
			edges.emplace(b, a);
			graph[a].emplace_back(b);
			graph[b].emplace_back(a);
			break;
		}
	}
	debug(graph);

	const auto color = coloring(graph, limit);
	debug(color);
	assert(ssize(color) == n);
	for (auto c : color)
		assert(c >= 0 and c < limit);
	REP(i, n)
		for (int x : graph[i])
			assert(color[i] != color[x]);
}
