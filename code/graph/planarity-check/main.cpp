/*
 * Opis: O(szybko) ale istnieją przykłady O(n^2), przyjmuje graf nieskierowany bez pętelek i multikrawędzi.
 */

bool is_planar(vector<vector<int>> graph) {
	int n = ssize(graph), m = 0;
	REP(v, n)
		m += ssize(graph[v]);
	m /= 2;
	if(n <= 3) return true;
	if(m > 3 * n - 6) return false;
	vector<vector<int>> up(n), dn(n);
	vector<int> low(n, -1), pre(n);
	REP(start, n)
		if(low[start] == -1) {
			vector<pair<int, int>> e_up;
			int tm = 0;
			function<void (int, int)> dfs_low = [&](int v, int p) {
				low[v] = pre[v] = tm++;
				for(int u : graph[v])
					if(u != p and low[u] == -1) {
						dn[v].emplace_back(u);
						dfs_low(u, v);
						low[v] = min(low[v], low[u]);
					}
					else if(u != p and pre[u] < pre[v]) {
						up[v].emplace_back(ssize(e_up));
						e_up.emplace_back(v, u);
						low[v] = min(low[v], pre[u]);
					}
			};
			dfs_low(start, -1);
			vector<pair<int, bool>> dsu(ssize(e_up));
			REP(v, ssize(dsu)) dsu[v].first = v;
			function<pair<int, bool> (int)> find = [&](int v) {
				if(dsu[v].first == v)
					return pair(v, false);
				auto [u, ub] = find(dsu[v].first);
				return dsu[v] = pair(u, ub ^ dsu[v].second);
			};
			auto onion = [&](int x, int y, bool flip) {
				auto [v, vb] = find(x);
				auto [u, ub] = find(y);
				if(v == u)
					return not (vb ^ ub ^ flip);
				dsu[v] = {u, vb ^ ub ^ flip};
				return true;
			};
			auto interlace = [&](const vector<int> &ids, int lo) {
				vector<int> ans;
				for(int e : ids)
					if(pre[e_up[e].second] > lo)
						ans.emplace_back(e);
				return ans;
			};
			auto add_fu = [&](const vector<int> &a, const vector<int> &b) {
				FOR(k, 1, ssize(a) - 1)
					if(not onion(a[k - 1], a[k], 0))
						return false;
				FOR(k, 1, ssize(b) - 1)
					if(not onion(b[k - 1], b[k], 0))
						return false;
				return a.empty() or b.empty() or onion(a[0], b[0], 1);
			};
			function<bool (int, int)> dfs_planar = [&](int v, int p) {
				for(int u : dn[v])
					if(not dfs_planar(u, v))
						return false;
				REP(i, ssize(dn[v])) {
					FOR(j, i + 1, ssize(dn[v]) - 1)
						if(not add_fu(interlace(up[dn[v][i]], low[dn[v][j]]),
									  interlace(up[dn[v][j]], low[dn[v][i]])))
							return false;
					for(int j : up[v]) {
						if(e_up[j].first != v)
							continue;
						if(not add_fu(interlace(up[dn[v][i]], pre[e_up[j].second]),
									  interlace({j}, low[dn[v][i]])))
							return false;
					}
				}
				for(int u : dn[v]) {
					for(int idx : up[u])
						if(pre[e_up[idx].second] < pre[p])
							up[v].emplace_back(idx);
					exchange(up[u], {});
				}
				return true;
			};
			if(not dfs_planar(start, -1))
				return false;
		}
	return true;
}
