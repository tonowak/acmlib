/*
 * Opis: Operacje na wielomianach mod $998244353$,
 * deriv, integr O(n), powi\_deg O(n \cdot deg), sqrt, inv, log, exp, powi, div O(n \log n), powi\_slow, eval, inter O(n \log ^2 n)
 * Ogólnie to przepisujemy co chcemy.
 * Funkcje oznaczone jako KONIECZNE są wymagane. Funkcje oznaczone WYMAGA ABC wymagają wcześniejszego przepisania ABC.
 * \texttt{deriv(a)} zwraca $a'$,
 * \texttt{integr(a)} zwraca $\int a$,
 * \texttt{powi(\_deg\_slow)(a, k, n)} zwraca $a^k (\bmod x^n)$,
 * \texttt{sqrt(a, n)} zwraca $a\^{}\frac{1}{2} (\bmod x^n)$,
 * \texttt{inv(a, n)} zwraca $a^{-1} (\bmod x^n)$,
 * \texttt{log(a, n)} zwraca $ln(a) (\bmod x^n)$,
 * \texttt{exp(a, n)} zwraca $exp(a) (\bmod x^n)$,
 * \texttt{div(a, b)} zwraca $(q, r)$ takie, że $a = qb + r$,
 * \texttt{eval(a, x)} zwraca $y$ taki, że $a(x_i) = y_i$,
 * \texttt{inter(x, y)} zwraca $a$ taki, że $a(x_i) = y_i$.
 */
#include "../ntt/main.cpp"
// BEGIN HASH
vi mod_xn(const vi& a, int n) { // KONIECZNE
	return vi(a.begin(), a.begin() + min(n, ssize(a)));
}
void sub(vi& a, const vi& b) { // KONIECZNE
	a.resize(max(ssize(a), ssize(b)));
	REP(i, ssize(b)) a[i] = sub(a[i], b[i]);
} // END HASH
// BEGIN HASH
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
} // END HASH
// BEGIN HASH
vi powi_deg(const vi& a, int k, int n) {
	assert(ssize(a) and a[0] != 0);
	vi v(n), f(n, 1);
	v[0] = powi(a[0], k);
	REP(i, n - 1) f[i + 1] = mul(f[i], n - i);
	int r = inv(mul(f[n - 1], a[0]));
	FOR(i, 1, n - 1) {
		FOR(j, 1, min(ssize(a) - 1, i)) {
			v[i] = add(v[i], mul(a[j], mul(v[i - j], sub(mul(k, j), i - j))));
		}
		v[i] = mul(v[i], mul(r, f[n - i]));
		r = mul(r, i);
	}
	return v;
} // END HASH
// BEGIN HASH
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
} // END HASH
// BEGIN HASH
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
} // END HASH
// BEGIN HASH
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
} // END HASH
// BEGIN HASH
vi log(const vi& a, int n) { // WYMAGA deriv, integr, inv
	assert(ssize(a) and a[0] == 1);
	return integr(mod_xn(conv(deriv(mod_xn(a, n)), inv(a, n)), n - 1));
} // END HASH
// BEGIN HASH
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
} // END HASH
// BEGIN HASH
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
} // END HASH
// BEGIN HASH
pair<vi, vi> div_slow(vi a, const vi& b) {
	vi x;
	while(ssize(a) >= ssize(b)) {
		x.emplace_back(mul(a.back(), inv(b.back())));
		if(x.back() != 0)
			REP(i, ssize(b))
				a.end()[-i - 1] = sub(a.end()[-i - 1], mul(x.back(), b.end()[-i - 1]));
		a.pop_back();
	}
	reverse(x.begin(), x.end());
	return {x, a};
}
pair<vi, vi> div(vi a, const vi& b) { // WYMAGA inv, div_slow
	const int d = ssize(a) - ssize(b) + 1;
	if (d <= 0)
		return {{}, a};
	if (min(d, ssize(b)) < 250)
		return div_slow(a, b);
	vi x = mod_xn(conv(mod_xn({a.rbegin(), a.rend()}, d), inv({b.rbegin(), b.rend()}, d)), d);
	reverse(x.begin(), x.end());
	sub(a, conv(x, b));
	return {x, mod_xn(a, ssize(b))};
} // END HASH
// BEGIN HASH
vi build(vector<vi> &tree, int v, auto l, auto r) {
	if (r - l == 1) {
		return tree[v] = vi{sub(0, *l), 1};
	} else {
		auto M = l + (r - l) / 2;
		return tree[v] = conv(build(tree, 2 * v, l, M), build(tree, 2 * v + 1, M, r));
	}
} // END HASH
// BEGIN HASH
int eval_single(const vi& a, int x) {
	int y = 0;
	for (int i = ssize(a) - 1; i >= 0; --i) {
		y = mul(y, x);
		y = add(y, a[i]);
	}
	return y;
}
vi eval_helper(const vi& a, vector<vi>& tree, int v, auto l, auto r) {
	if (r - l == 1) {
		return {eval_single(a, *l)};
	} else {
		auto m = l + (r - l) / 2;
		vi A = eval_helper(div(a, tree[2 * v]).second, tree, 2 * v, l, m);
		vi B = eval_helper(div(a, tree[2 * v + 1]).second, tree, 2 * v + 1, m, r);
		A.insert(A.end(), B.begin(), B.end());
		return A;
	}
}
vi eval(const vi& a, const vi& x) { // WYMAGA div, eval_single, build, eval_helper
	if (x.empty())
		return {};
	vector<vi> tree(4 * ssize(x));
	build(tree, 1, begin(x), end(x));
	return eval_helper(a, tree, 1, begin(x), end(x));
} // END HASH
// BEGIN HASH
vi inter_helper(const vi& a, vector<vi>& tree, int v, auto l, auto r, auto ly, auto ry) {
	if (r - l == 1) {
		return {mul(*ly, inv(a[0]))};
	}
	else {
		auto m = l + (r - l) / 2;
		auto my = ly + (ry - ly) / 2;
		vi A = inter_helper(div(a, tree[2 * v]).second, tree, 2 * v, l, m, ly, my);
		vi B = inter_helper(div(a, tree[2 * v + 1]).second, tree, 2 * v + 1, m, r, my, ry);
		vi L = conv(A, tree[2 * v + 1]);
		vi R = conv(B, tree[2 * v]);
		REP(i, ssize(R))
			L[i] = add(L[i], R[i]);
		return L;
	}
}
vi inter(const vi& x, const vi& y) { // WYMAGA deriv, div, build, inter_helper
	assert(ssize(x) == ssize(y));
	if (x.empty())
		return {};
	vector<vi> tree(4 * ssize(x));
	return inter_helper(deriv(build(tree, 1, begin(x), end(x))), tree, 1, begin(x), end(x), begin(y), end(y));
} // END HASH
