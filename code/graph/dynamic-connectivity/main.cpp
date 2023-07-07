/*
 * Opis: O(q\log^2 m), dla danych krawędzi i zapytań w postaci pary wierzchołków oraz listy indeksów krawędzi,
 * stwierdza offline, czy wierzchołki są w jednej spójnej w grafie powstałym przez wzięcie wszystkich krawędzi poza tymi z listy.
 */

struct DynamicConnectivity {
	int n, leaves = 1;
	vector<pair<int, int>> queries;
	vector<vector<pair<int, int>>> edges_to_add;
	DynamicConnectivity(int _n, vector<pair<int, int>> _queries) 
			: n(_n), queries(_queries) {
		while(leaves < ssize(queries))
			leaves *= 2;
		edges_to_add.resize(2 * leaves);
	}
	void add(int l, int r, pair<int, int> e) {
		if(l > r)
			return;
		l += leaves;
		r += leaves;
		while(l <= r) {
			if(l % 2 == 1)
				edges_to_add[l++].emplace_back(e);
			if(r % 2 == 0)
				edges_to_add[r--].emplace_back(e);
			l /= 2;
			r /= 2;
		}
	}
	void add_besides_points(vector<int> pts, pair<int, int> e) {
		if(pts.empty()) {
			add(0, ssize(queries) - 1, e);
			return;
		}
		sort(pts.begin(), pts.end());
		add(0, pts[0] - 1, e);
		REP(i, ssize(pts) - 1)
			add(pts[i] + 1, pts[i + 1] - 1, e);
		add(pts.back() + 1, ssize(queries) - 1, e);
	}
	vector<bool> get_answer() {
		vector<bool> ret(ssize(queries));
		vector<int> lead(n);
		vector<int> leadsz(n, 1);
		iota(lead.begin(), lead.end(), 0);
		function<int (int)> find = [&](int i) {
			return i == lead[i] ? i : find(lead[i]);
		};
		function<void (int)> dfs = [&](int v) {
			vector<tuple<int, int, int, int>> rollback;
			for(auto [e0, e1] : edges_to_add[v]) {
				e0 = find(e0);
				e1 = find(e1);
				if(e0 == e1)
					continue;
				if(leadsz[e0] > leadsz[e1])
					swap(e0, e1);
				rollback.emplace_back(make_tuple(e0, lead[e0], e1, leadsz[e1]));
				leadsz[e1] += leadsz[e0];
				lead[e0] = e1;
			}
			if(v >= leaves) {
				int i = v - leaves;
				assert(i < leaves);
				if(i < ssize(queries))
					ret[i] = find(queries[i].first) == find(queries[i].second);
			}
			else {
				dfs(2 * v);
				dfs(2 * v + 1);
			}
			reverse(rollback.begin(), rollback.end());
			for(auto [i, val, j, sz] : rollback) {
				lead[i] = val;
				leadsz[j] = sz;
			}
		};
		dfs(1);
		return ret;
	}
};
