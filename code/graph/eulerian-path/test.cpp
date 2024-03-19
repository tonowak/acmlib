#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	constexpr int N = 10, M = 12;
	const int n = rd(1, N);
	const int m = rd(0, M);
	const bool directed = rd(0, 1);
	vector<pair<int, int>> edges;
	REP(i, m)
		edges.emplace_back(rd(0, n - 1), rd(0, n - 1));
	debug(n, m, directed, edges);

	EulerRet ep = eulerian_path(n, edges, directed);

	bool exists = m ? false : true;
	REP(start, n) {
		vector<bool> used(m);
		function<bool(int, int)> gen = [&](int last, int len) -> bool {
			if (len == m) {
				return true;
			}
			REP(id, m) {
				if (used[id])
					continue;
				auto [a, b] = edges[id];
				if (not (last == a or (not directed and last == b)))
					continue;
				int next = last ^ a ^ b;
				used[id] = true;
				if (gen(next, len + 1))
					return true;
				used[id] = false;
			}
			return false;
		};
		exists = gen(start, 0);
		if (exists)
			break;
	}
	debug(exists, ep.exists);
	assert(exists == ep.exists);

	if (exists) {
		int v = ep.vertices.empty() ? 0 : ep.vertices.front();
		const auto ids = ep.ids;
		assert(v >= 0 and v < n);
		assert(ssize(ids) == m);
		for (int id : ids)
			assert(id >= 0 and id < m);
		set<int> sids(ids.begin(), ids.end());
		assert(ssize(sids) == ssize(ids));
		for (int id : ids) {
			auto [a, b] = edges[id];
			if (directed) {
				assert(a == v);
				v = b;
			}
			else {
				assert(v == a or v == b);
				v ^= a ^ b;
			}
		}
		const auto vertices = ep.vertices;
		assert((m == 0 and ep.vertices.empty()) or (m > 0 and ssize(vertices) == m + 1));
		for (int x : vertices)
			assert(x >= 0 and x < n);
		REP(i, m) {
			auto a = vertices[i];
			auto b = vertices[i + 1];
			auto it = find(edges.begin(), edges.end(), pair(a, b));
			if (it != edges.end()) {
				edges.erase(it);
				continue;
			}
			assert(not directed);
			it = find(edges.begin(), edges.end(), pair(b, a));
			assert(it != edges.end());
			edges.erase(it);
		}
	}
}
