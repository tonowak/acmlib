/*
 * Opis: podstawowe operacje na modulo,
 * pamiętać o constexpr.
 */
#pragma once
#ifdef CHANGABLE_MOD
int mod = 998'244'353;
#else
constexpr int mod = 998'244'353;
#endif
int add(int a, int b) {
	a += b;
	return a >= mod ? a - mod : a;
}
int sub(int a, int b) {
	return add(a, mod - b);
}
int mul(int a, int b) {
	return int(a * LL(b) % mod);
}
int powi(int a, int b) {
	for(int ret = 1;; b /= 2) {
		if(b == 0)
			return ret;
		if(b & 1)
			ret = mul(ret, a);
		a = mul(a, a);
	}
}
int inv(int x) {
	return powi(x, mod - 2);
}
struct BinomCoeff {
	vector<int> fac, rev;
	BinomCoeff(int n) {
		fac = rev = vector(n + 1, 1);
		FOR(i, 1, n) fac[i] = mul(fac[i - 1], i);
		rev[n] = inv(fac[n]);
		for(int i = n; i > 0; --i)
			rev[i - 1] = mul(rev[i], i);
	}
	int operator()(int n, int k) {
		return mul(fac[n], mul(rev[n - k], rev[k]));
	}
};
