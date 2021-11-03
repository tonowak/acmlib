/*
 * Opis: Liczy $\sum_{i=0}^{n-1} \left\lfloor \frac{a\cdot i + b}{c} \right\rfloor$
 * Czas: O(\log(a))
 * Użycie: floor_sum(n, a, b, c)
 * Działa dla $0 \leq a, b < c$ oraz $1\leq c, n \leq 10^9$.
 * Dla innych $n, a, b, c$ trzeba uważać lub użyć __int128.
 */

LL floor_sum(LL n, LL a, LL b, LL c) {
	LL ans = 0;
	if (a >= c) {
		ans += (n - 1) * n * (a / c) / 2;
		a %= c;
	}
	if (b >= c) {
		ans += n * (b / c);
		b %= c;
	}
	LL d = (a * (n - 1) + b) / c;
	if (d == 0) return ans;
	ans += d * (n - 1) - floor_sum(d, c, c - b - 1, a);
	return ans;
}
