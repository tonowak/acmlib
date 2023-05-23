/*
 * Opis: DP 1D1D
 * Czas: O(n \log n)
 * Użycie:
 *   n - długość paska (n > 0)
 *   cost(i, j) - koszt odcinka [i, j]
 *   Dla a <= b <= c <= d, cost spełnia cost(a, c) + cost(b, d) <= cost(a, d) + cost(b, c).
 *   Dzieli pasek [0, n) na odcinki [0, cuts[0]], ..., (cuts[i-1], cuts[i]],
 *   gdzie cuts.back() == n - 1, aby sumaryczny koszt wszystkich odcinków był minimalny.
 *   Zwraca (opt_cost, cuts).
 *   Aby maksymalizować koszt zamienić nierówności tam, gdzie wskazane.
 *   Aby uzyskać O(n), należy przepisać overtake w oparciu o dodatkowe założenia,
 *   aby chodził w O(1).
 */

pair<LL, vector<int>> dp_1d1d(int n, function<LL (int, int)> cost) {
	vector<pair<LL, int>> dp(n);
	vector<int> lf(n + 2), rg(n + 2), dead(n);
	vector<vector<int>> events(n + 1);
	int beg = n, end = n + 1;
	rg[beg] = end; lf[end] = beg;

	auto score = [&](int i, int j) {
		return dp[j].first + cost(j + 1, i);
	};

	auto overtake = [&](int a, int b, int mn) {
		int bp = mn - 1, bk = n;
		while (bk - bp > 1) {
			int bs = (bp + bk) / 2;
			if (score(bs, a) <= score(bs, b)) // tu zamienić na >=
				bk = bs;
			else
				bp = bs;
		}
		return bk;
	};

	auto add = [&](int i, int mn) {
		if (lf[i] == beg)
			return;
		events[overtake(i, lf[i], mn)].emplace_back(i);
	};

	REP (i, n) {
		dp[i] = {cost(0, i), -1};
		REP (j, ssize(events[i])) {
			int x = events[i][j];
			if (dead[x])
				continue;
			dead[lf[x]] = 1; lf[x] = lf[lf[x]];
			rg[lf[x]] = x; add(x, i);
		}
		if (rg[beg] != end)
			dp[i] = min(dp[i], {score(i, rg[beg]), rg[beg]}); // tu max
		lf[i] = lf[end]; rg[i] = end;
		rg[lf[i]] = i; lf[rg[i]] = i;
		add(i, i + 1);
	}

	vector<int> cuts;
	for (int p = n - 1; p != -1; p = dp[p].second)
		cuts.emplace_back(p);
	reverse(cuts.begin(), cuts.end());
	return pair(dp[n - 1].first, cuts);
}
