/*
 * Opis: O(n^\frac{1}{4}),
 * \texttt{factor(n)} zwraca vector dzielników pierwszych $n$, niekoniecznie posortowany,
 * \texttt{get\_pairs(n)} zwraca posortowany vector par (dzielnik pierwszych, krotność) dla liczby $n$,
 * \texttt{all\_factors(n)} zwraca vector wszystkich dzielników $n$, niekoniecznie posortowany,
 * \texttt{factor(12) = \{2, 2, 3\}, factor(545423) = \{53, 41, 251\};},
 * \texttt{get\_pairs(12) = \{(2, 2), (3, 1)\}},
 * \texttt{all\_factors(12) = \{1, 3, 2, 6, 4, 12\}}.
 */

#include "../miller-rabin/main.cpp"

LL rho_pollard(LL n) {
	if(n % 2 == 0) return 2;
	for(LL i = 1;; i++) {
		auto f = [&](LL x) { return (llmul(x, x, n) + i) % n; };
		LL x = 2, y = f(x), p;
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

vector<pair<LL, int>> get_pairs(LL n) {
	auto v = factor(n);
	sort(v.begin(), v.end());
	vector<pair<LL, int>> ret;
	REP(i, ssize(v)) {
		int x = i + 1;
		while (x < ssize(v) and v[x] == v[i])
			++x;
		ret.emplace_back(v[i], x - i);
		i = x - 1;
	}
	return ret;
}

vector<LL> all_factors(LL n) {
	auto v = get_pairs(n);
	vector<LL> ret;
	function<void(LL,int)> gen = [&](LL val, int p) {
		if (p == ssize(v)) {
			ret.emplace_back(val);
			return;
		}
		auto [x, cnt] = v[p];
		gen(val, p + 1);
		REP(i, cnt) {
			val *= x;
			gen(val, p + 1);
		}
	};
	gen(1, 0);
	return ret;
}
