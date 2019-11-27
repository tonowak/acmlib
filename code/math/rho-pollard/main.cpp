/*
 * Opis: Rozkład na czynniki Rho Pollarda
 * Czas: O(n^{\frac{1}{4}})
 */

#include "../miller-rabin/main.cpp"
LL rho_pollard(LL n) {
	auto f = [&](LL x) { return (mul(x, x, n) + 1) % n; };
	if(n % 2 == 0) return 2;
	for(LL i = 2;; i++) {
		LL x = i, y = f(x), p;
		while((p = __gcd(n - x + y, n)) == 1)
			x = f(x), y = f(f(y));
		if(p != n) return p;
	}
}

vector<LL> factor(LL n) {
	if(n == 1) return {};
	if(miller_rabin(n)) return {n};
	LL x = rho_pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}
