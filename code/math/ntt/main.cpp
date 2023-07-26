/*
 * Opis: O(n\log n) mnożenie wielomianów mod $998244353$.
 */
#include "../simple-modulo/main.cpp"
using vi = vector<int>;
constexpr int root = 3;
void ntt(vi& a, int n, bool inverse = false) {
	assert((n & (n - 1)) == 0);
	a.resize(n);
	vi b(n);
	for(int w = n / 2; w; w /= 2, swap(a, b)) {
		int r = powi(root, (mod - 1) / n * w), m = 1;
		for(int i = 0; i < n; i += w * 2, m = mul(m, r)) REP(j, w) {
			int u = a[i + j], v = mul(a[i + j + w], m);
			b[i / 2 + j] = add(u, v);
			b[i / 2 + j + n / 2] = sub(u, v);
		}
	}
	if(inverse) {
		reverse(a.begin() + 1, a.end());
		int invn = inv(n);
		for(int& e : a) e = mul(e, invn);
	}
}
vi conv(vi a, vi b) {
	if(a.empty() or b.empty()) return {};
	int l = ssize(a) + ssize(b) - 1, sz = 1 << __lg(2 * l - 1);
	ntt(a, sz), ntt(b, sz);
	REP(i, sz) a[i] = mul(a[i], b[i]);
	ntt(a, sz, true), a.resize(l);
	return a;
}
