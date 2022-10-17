/*
 * Opis: power_monomial_sum(a, k, n) liczy $\sum_{i=0}^{n-1} a^i \cdot i^k, power_binomial_sum(a, k, n) liczy $\sum_{i=0}^{n-1} a^i \cdot binom{i}{k}
 * Czas: power_monomial_sum - O(k ^ 2 * \log(mod)), power_binomial_sum - O(k * \log(mod))
 * Użycie: power_monomial_sum(a, k, n), power_binomial_sum(a, k, n)
 * Działa dla $0 \leq n$ oraz $a\neq 1$.
 */
#include "../simple-modulo/main.cpp"

int power_monomial_sum(int a, int k, int n) {
	const int powan = powi(a, n);
	const int inva1 = inv(sub(a, 1));
	int monom = 1, ans = 0;
	vector<int> v(k + 1);
	REP(i, k + 1) {
		int binom = 1, sum = 0;
		REP(j, i) {
			sum = add(sum, mul(binom, v[j]));
			binom = mul(binom, mul(i - j, inv(j + 1)));
		}
		ans = sub(mul(powan, monom), mul(sum, a));
		if(!i) ans = sub(ans, 1);
		ans = mul(ans, inva1);
		v[i] = ans;
		monom = mul(monom, n);
	}
	return ans;
}

int power_binomial_sum(int a, int k, int n) {
	const int powan = powi(a, n);
	const int inva1 = inv(sub(a, 1));
	int binom = 1, ans = 0;
	REP(i, k + 1) {
		ans = sub(mul(powan, binom), mul(ans, a));
		if(!i) ans = sub(ans, 1);
		ans = mul(ans, inva1);
		binom = mul(binom, mul(n - i, inv(i + 1)));
	}
	return ans;
}
