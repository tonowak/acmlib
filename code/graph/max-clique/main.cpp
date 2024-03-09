/*
 * Opis: O(idk), działa 1s dla n=155 na najgorszych przypadkach
 * (losowe grafy p=.90). Działa szybciej dla grafów rzadkich.
 * Zwraca listę wierzchołków w jakiejś max klice. Pętelki niedozwolone.
 */
constexpr int max_n = 500;
vector<int> get_max_clique(vector<bitset<max_n>> e) {
	double limit = 0.025, pk = 0;
	vector<pair<int, int>> V;
	vector<vector<int>> C(ssize(e) + 1);
	vector<int> qmax, q, S(ssize(C)), old(S);
	REP(i, ssize(e)) V.emplace_back(0, i);
	auto init = [&](vector<pair<int, int>>& r) {
		for (auto& v : r) for (auto j : r) v.first += e[v.second][j.second];
		sort(r.rbegin(), r.rend());
		int mxD = r[0].first;
		REP(i, ssize(r)) r[i].first = min(i, mxD) + 1;
	};
	function<void (vector<pair<int, int>>&, int)> expand = [&](vector<pair<int, int>>& R, int lev) {
		S[lev] += S[lev - 1] - old[lev];
		old[lev] = S[lev - 1];
		while (ssize(R)) {
			if (ssize(q) + R.back().first <= ssize(qmax)) return;
			q.emplace_back(R.back().second);
			vector<pair<int, int>> T;
			for(auto [_, v] : R) if (e[R.back().second][v]) T.emplace_back(0, v);
			if (ssize(T)) {
				if (S[lev]++ / ++pk < limit) init(T);
				int j = 0, mxk = 1, mnk = max(ssize(qmax) - ssize(q) + 1, 1);
				C[1] = C[2] = {};
				for (auto [_, v] : T) {
					int k = 1;
					while (any_of(C[k].begin(), C[k].end(), [&](int i) { return e[v][i]; })) k++;
					if (k > mxk) C[(mxk = k) + 1] = {};
					if (k < mnk) T[j++].second = v;
					C[k].emplace_back(v);
				}
				if (j > 0) T[j - 1].first = 0;
				FOR(k, mnk, mxk) for (int i : C[k]) T[j++] = {k, i};
				expand(T, lev + 1);
			} else if (ssize(q) > ssize(qmax)) qmax = q;
			q.pop_back(), R.pop_back();
		}
	};
	init(V), expand(V, 1); return qmax;
}
