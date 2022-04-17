/*
 * Opis: Mnożenie wielomianów mod 998244353
 * Czas: O(n \log n)
 * Użycie:
 *   conv(a, b) zwraca iloczyn wielomianów a i b
 */

#include "../simple-modulo/main.cpp" 

const int root = [] {
	if(mod == -1) // if for testing
		mod = 998'244'353;
	for(int r = 2;; ++r)
		if(powi(r, (mod - 1) / 2) != 1)
			return r;
}();
void ntt(vector<int> &a, bool inverse = false) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	static vector<int> dt(30), idt(30);
	if(dt[0] == 0)
		for(int i = 0; i < 30; ++i) {
			dt[i] = sub(0, powi(root, (mod - 1) >> (i + 2)));
			idt[i] = inv(dt[i]);
		}
	if(not inverse) {
		for(int w = n; w >>= 1; ) {
			int t = 1;
			for(int s = 0, k = 0; s < n; s += 2 * w) {
				for(int i = s, j = s + w; i < s + w; ++i, ++j) {
					int x = a[i], y = mul(a[j], t);
					a[i] = add(x, y);
					a[j] = sub(x, y);
				}
				t = mul(t, dt[__builtin_ctz(++k)]);
			}
		}
	} else {
		for(int w = 1; w < n; w *= 2) {
			int t = 1;
			for(int s = 0, k = 0; s < n; s += 2 * w) {
				for(int i = s, j = s + w; i < s + w; ++i, ++j) {
					int x = a[i], y = a[j];
					a[i] = add(x, y);
					a[j] = mul(sub(x, y), t);
				}
				t = mul(t, idt[__builtin_ctz(++k)]);
			}
		}
	}
}
vector<int> conv(vector<int> a, vector<int> b) {
	if(a.empty() or b.empty()) return {};
	int n = ssize(a), m = ssize(b), l = n + m - 1, sz = 1 << __lg(2 * l - 1);
	a.resize(sz), ntt(a);
	b.resize(sz), ntt(b);
	REP(i, sz) a[i] = mul(a[i], b[i]);
	ntt(a, true), a.resize(l);
	int invsz = inv(sz);
	for(int &e : a) e = mul(e, invsz);
	return a;
}

