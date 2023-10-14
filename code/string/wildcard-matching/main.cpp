/*
 * Opis: O(n \log n), zwraca tablicę wystąpień wzorca. Alfabet od 0. Znaki zapytania to -1. Mogą być zarówno w tekście jak i we wzrocu. Im większy alfabet tym bardziej trzeba uważać.
 */
#include "../../math/ntt/main.cpp"
vector<bool> wildcard_matching(vi text, vi pattern) {
	for (int& e : text) ++e;
	for (int& e : pattern) ++e;
	reverse(pattern.begin(), pattern.end());
	int n = ssize(text), m = ssize(pattern);
	int sz = 1 << __lg(2 * n - 1);
	vi a(sz), b(sz), c(sz);
	auto h = [&](auto f, auto g) {
		fill(a.begin(), a.end(), 0);
		fill(b.begin(), b.end(), 0);
		REP(i, n) a[i] = f(text[i]);
		REP(i, m) b[i] = g(pattern[i]);
		ntt(a, sz), ntt(b, sz);
		REP(i, sz) a[i] = mul(a[i], b[i]);
		ntt(a, sz, true);
		REP(i, sz) c[i] = add(c[i], a[i]);
	};
	h([](int x){return powi(x,3);},identity());
	h([](int x){return sub(0, mul(2, mul(x, x)));}, [](int x){return mul(x, x);});
	h(identity(),[](int x){return powi(x,3);});
	vector<bool> ret(n - m + 1);
	FOR(i, m, n) ret[i - m] = !c[i - 1];
	return ret;
}
