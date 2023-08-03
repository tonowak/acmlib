/*
 * Opis: O(q\log^2 n) offline, zaczyna z pustym grafem, dla danego zapytania stwierdza czy wierzchołki sa w jednej spójnej.
 *   Multikrawędzie oraz pętelki działają.
 */
enum Event_type { Add, Remove, Query };
vector<bool> dynamic_connectivity(int n, vector<tuple<int, int, Event_type>> events) {
	vector<pair<int, int>> queries;
	for(auto &[v, u, t] : events) {
		if(v > u)
			swap(v, u);
		if(t == Query)
			queries.emplace_back(v, u);
	}
	int leaves = 1;
	while(leaves < ssize(queries))
		leaves *= 2;
	vector<vector<pair<int, int>>> edges_to_add(2 * leaves);
	map<pair<int, int>, deque<int>> edge_longevity;
	int query_i = 0;
	auto add = [&](int l, int r, pair<int, int> e) {
		if(l > r)
			return;
		debug(l, r, e);
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
	};
	for(const auto &[v, u, t] : events) {
		auto &que = edge_longevity[pair(v, u)];
		if(t == Add)
			que.emplace_back(query_i);
		else if(t == Remove) {
			if(que.empty())
				continue;
			if(ssize(que) == 1)
				add(que.back(), query_i - 1, pair(v, u));
			que.pop_back();
		}
		else
			++query_i;
	}
	for(const auto &[e, que] : edge_longevity)
		if(not que.empty())
			add(que.front(), query_i - 1, e);
	vector<bool> ret(ssize(queries));
	vector<int> lead(n), leadsz(n, 1);
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
			rollback.emplace_back(e0, lead[e0], e1, leadsz[e1]);
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
