/*
 * Opis: podstawowe operacje na modulo.
 * Użycie: pamiętać o constexpr.
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
