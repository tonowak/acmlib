/*
 * Opis: power\_monomial\_sum O(k \log k), power\_binomial\_sum O(k).
 * power\_monomial\_sum(a, k, n) liczy $\sum_{i=0}^{n-1} a^i \cdot i^k$, power\_binomial\_sum(a, k, n) liczy $\sum_{i=0}^{n-1} a^i \cdot {i \choose k}$.
 * Działa dla $0 \leq n$ oraz $a \neq 1$.
 */
#include "../lagrange-consecutive/main.cpp"
// BEGIN HASH
int power_monomial_sum(int a, int k, int n) {
	if (n == 0) return 0;
	int p = 1, b = 1, c = 0, d = a, inva = inv(a);
	vector<int> v(k + 1, k == 0);
	FOR(i, 1, k) v[i] = add(v[i - 1], mul(p = mul(p, a), powi(i, k)));
	BinomCoeff bc(k + 1);
	REP(i, k + 1) {
		c = add(c, mul(bc(k + 1, i), mul(v[k - i], b)));
		b = mul(b, sub(0, a));
	}
	c = mul(c, inv(powi(sub(1, a), k + 1)));
	REP(i, k + 1) v[i] = mul(sub(v[i], c), d = mul(d, inva));
	return add(c, mul(lagrange_consecutive(v, n - 1), powi(a, n - 1)));
} // END HASH
// BEGIN HASH
int power_binomial_sum(int a, int k, int n) {
	int p = powi(a, n), inva1 = inv(sub(a, 1)), binom = 1, ans = 0;
	BinomCoeff bc(k + 1);
	REP(i, k + 1) {
		ans = sub(mul(p, binom), mul(ans, a));
		if(!i) ans = sub(ans, 1);
		ans = mul(ans, inva1);
		binom = mul(binom, mul(n - i, mul(bc.rev[i + 1], bc.fac[i])));
	}
	return ans;
} // END HASH
