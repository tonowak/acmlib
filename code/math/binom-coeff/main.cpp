/*
 * Opis: Symbole newtona
 * Czas: O(n \log n + q)
 * Użycie: b(n, k) zwraca n po k
 */
#include "../mod-int/main.cpp"
struct BinomCoeff {
	vector<mint> fac, rev;
	BinomCoeff(int n) {
		fac = rev = vector<mint>(n + 1, 1);
		FOR(i, 1, n) fac[i] = fac[i - 1] * i;
		rev[n] = 1 / fac[n];
		for(int i = n; i >= 1; i--)
			rev[i - 1] = rev[i] * i;
	}
	mint operator()(int n, int k) {
		return fac[n] * rev[n - k] * rev[k];
	}
};
