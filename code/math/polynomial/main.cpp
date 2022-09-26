/*
 * Opis: Operacje na wielomianach mod 998244353
 * Czas: deriv, integr - O(n), powi_deg - O(n * deg), sqrt, inv, log, exp, powi - O(n * \log n), powi_slow, eval, inter - O(n * \log ^2 n)
 * Użycie:
 *   Ogólnie to przepisujemy co chcemy. Funkcje oznaczone jako KONIECZNE są wymagane od miejsca ich wystąpienia w kodzie. Funkcje oznaczone WYMAGA ABC wymagają wcześniejszego przepisania ABC.
 *   deriv(a) zwraca a'
 *   integr(a) zwraca ∫a
 *   powi*(a, k, n) zwraca a^k (mod x^n)
 *   sqrt(a, n) zwraca a^1/2 (mod x^n)
 *   inv(a, n) zwraca a^-1 (mod x^n)
 *   log(a, n) zwraca ln(a) (mod x^n)
 *   exp(a, n) zwraca exp(a) (mod x^n)
 *   eval(a, x) zwraca y taki, że a(x_i) = y_i
 *   inter(x, y) zwraca a taki, że a(x_i) = y_i
 */

#include "../ntt/main.cpp"

vi deriv(vi a) {
	REP(i, ssize(a)) a[i] = mul(a[i], i);
	if(ssize(a)) a.erase(a.begin());
	return a;
}

vi integr(vi a) {
	int n = ssize(a);
	a.insert(a.begin(), 0);
	static vi f{1};
	FOR(i, ssize(f), n) f.emplace_back(mul(f[i - 1], i));
	int r = inv(f[n]);
	for(int i = n; i > 0; --i)
		a[i] = mul(a[i], mul(r, f[i - 1])), r = mul(r, i);
	return a;
}

vi powi_deg(const vi& a, int k, int n) {
	assert(ssize(a) and a[0] != 0);
	vi v(n);
	v[0] = powi(a[0], k);
	FOR(i, 1, n - 1) {
		FOR(j, 1, min(ssize(a) - 1, i)) {
			v[i] = add(v[i], mul(a[j], mul(v[i - j], sub(mul(k, j), i - j))));
		}
		v[i] = mul(v[i], inv(mul(i, a[0])));
	}
	return v;
}

vi mod_xn(const vi& a, int n) { // KONIECZNE
	return vi(a.begin(), a.begin() + min(n, ssize(a)));
}

vi powi_slow(const vi &a, int k, int n) {
	vi v{1}, b = mod_xn(a, n);
	int x = 1; while(x < n) x *= 2;
	while(k) {
		ntt(b, 2 * x);
		if(k & 1) {
			ntt(v, 2 * x);
			REP(i, 2 * x) v[i] = mul(v[i], b[i]);
			ntt(v, 2 * x, true);
			v.resize(x);
		}
		REP(i, 2 * x) b[i] = mul(b[i], b[i]);
		ntt(b, 2 * x, true);
		b.resize(x);
		k /= 2;
	}
	return mod_xn(v, n);
}

vi sqrt(const vi& a, int n) {
	auto at = [&](int i) { if(i < ssize(a)) return a[i]; else return 0; };
	assert(ssize(a) and a[0] == 1);
	const int inv2 = inv(2);
	vi v{1}, f{1}, g{1};
	for(int x = 1; x < n; x *= 2) {
		vi z = v;
		ntt(z, x);
		vi b = g;
		REP(i, x) b[i] = mul(b[i], z[i]);
		ntt(b, x, true);
		REP(i, x / 2) b[i] = 0;
		ntt(b, x);
		REP(i, x) b[i] = mul(b[i], g[i]);
		ntt(b, x, true);
		REP(i, x / 2) f.emplace_back(sub(0, b[i + x / 2]));
		REP(i, x) z[i] = mul(z[i], z[i]);
		ntt(z, x, true);
		vi c(2 * x);
		REP(i, x) c[i + x] = sub(add(at(i), at(i + x)), z[i]);
		ntt(c, 2 * x);
		g = f;
		ntt(g, 2 * x);
		REP(i, 2 * x) c[i] = mul(c[i], g[i]);
		ntt(c, 2 * x, true);
		REP(i, x) v.emplace_back(mul(c[i + x], inv2));
	}
	return mod_xn(v, n);
}

void sub(vi& a, const vi& b) { // KONIECZNE
	a.resize(max(ssize(a), ssize(b)));
	REP(i, ssize(b)) a[i] = sub(a[i], b[i]);
}

vi inv(const vi& a, int n) {
	assert(ssize(a) and a[0] != 0);
	vi v{inv(a[0])};
	for(int x = 1; x < n; x *= 2) {
		vi f = mod_xn(a, 2 * x), g = v;
		ntt(g, 2 * x);
		REP(k, 2) {
			ntt(f, 2 * x);
			REP(i, 2 * x) f[i] = mul(f[i], g[i]);
			ntt(f, 2 * x, true);
			REP(i, x) f[i] = 0;
		}
		sub(v, f);
	}
	return mod_xn(v, n);
}

vi log(const vi& a, int n) { // WYMAGA deriv, integr, inv
	assert(ssize(a) and a[0] == 1);
	return integr(mod_xn(conv(deriv(mod_xn(a, n)), inv(a, n)), n - 1));
}

vi exp(const vi& a, int n) { // WYMAGA deriv, integr
	assert(a.empty() or a[0] == 0);
	vi v{1}, f{1}, g, h{0}, s;
	for(int x = 1; x < n; x *= 2) {
		g = v;
		REP(k, 2) {
			ntt(g, (2 - k) * x);
			if(!k) s = g;
			REP(i, x) g[i] = mul(g[(2 - k) * i], h[i]);
			ntt(g, x, true);
			REP(i, x / 2) g[i] = 0;
		}
		sub(f, g);
		vi b = deriv(mod_xn(a, x));
		ntt(b, x);
		REP(i, x) b[i] = mul(s[2 * i], b[i]);
		ntt(b, x, true);
		vi c = deriv(v);
		sub(c, b);
		rotate(c.begin(), c.end() - 1, c.end());
		ntt(c, 2 * x);
		h = f;
		ntt(h, 2 * x);
		REP(i, 2 * x) c[i] = mul(c[i], h[i]);
		ntt(c, 2 * x, true);
		c.resize(x);
		vi t(x - 1);
		c.insert(c.begin(), t.begin(), t.end());
		vi d = mod_xn(a, 2 * x);
		sub(d, integr(c));
		d.erase(d.begin(), d.begin() + x);
		ntt(d, 2 * x);
		REP(i, 2 * x) d[i] = mul(d[i], s[i]);
		ntt(d, 2 * x, true);
		REP(i, x) v.emplace_back(d[i]);
	}
	return mod_xn(v, n);
}

vi powi(const vi& a, int k, int n) { // WYMAGA log, exp
	vi v = mod_xn(a, n);
	int cnt = 0;
	while(cnt < ssize(v) and !v[cnt])
		++cnt;
	if(LL(cnt) * k >= n)
		return {};
	v.erase(v.begin(), v.begin() + cnt);
	if(v.empty())
		return k ? vi{} : vi{1};
	int powi0 = powi(v[0], k);
	int inv0 = inv(v[0]);
	for(int& e : v) e = mul(e, inv0);
	v = log(v, n - cnt * k);
	for(int& e : v) e = mul(e, k);
	v = exp(v, n - cnt * k);
	for(int& e : v) e = mul(e, powi0);
	vi t(cnt * k, 0);
	v.insert(v.begin(), t.begin(), t.end());
	return v;
}

vi eval(const vi& a, const vi& x) {
	// TODO
	(void)a; (void)x;
	return {};
}

vi inter(const vi& x, const vi& y) {
	// TODO
	(void)x; (void)y;
	return {};
}
