/*
 * Opis: O(nm\log m), dla funkcji $cost(k,j)$ wylicza $dp(i,j) = min_{0\leq k\leq j}\; dp(i-1,k-1) + cost(k,j)$.
 *   Działa tylko wtedy, gdy $opt(i,j-1)\le opt(i,j)$,
 *   a jest to zawsze spełnione, gdy $cost(b,c)\le cost(a,d)$ oraz $cost(a,c) + cost(b,d)\le cost(a,d) + cost(b,c)$ dla $a\le b\le c\le d$.
 */
vector<LL> divide_and_conquer_optimization(int n, int m, function<LL(int,int)> cost) {
	vector<LL> dp_before(m);
	auto dp_cur = dp_before;
	REP(i, m)
		dp_before[i] = cost(0, i);
	function<void(int,int,int,int)> compute = [&](int l, int r, int optl, int optr) {
		if (l > r)
			return;
		int mid = (l + r) / 2, opt;
		pair<LL, int> best = {numeric_limits<LL>::max(), -1};
		FOR(k, optl, min(mid, optr))
			best = min(best, {(k ? dp_before[k - 1] : 0) + cost(k, mid), k});
		tie(dp_cur[mid], opt) = best;
		compute(l, mid - 1, optl, opt);
		compute(mid + 1, r, opt, optr);
	};
	REP(i, n) {
		compute(0, m - 1, 0, m - 1);
		swap(dp_before, dp_cur);
	}
	return dp_before;
}
