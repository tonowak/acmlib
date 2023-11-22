/*
 * Opis: O(n),
 *   \texttt{mobius(n)} oblicza funkcję M\"obiusa na [0..n],
 *   \texttt{totient(n)} oblicza funkcję Eulera na [0..n],
 *   wartości w $0$ niezdefiniowane.
 */
#include "../sieve/main.cpp"
// BEGIN HASH
vector<int> mobius(int n) {
	sieve(n);
	vector<int> ans(n + 1, 0);
	if (n) ans[1] = 1;
	FOR(i, 2, n) {
		int p = prime_div[i];
		if (i / p % p) ans[i] = -ans[i / p];
	}
	return ans;
} // END HASH
// BEGIN HASH
vector<int> totient(int n) {
	sieve(n);
	vector<int> ans(n + 1, 1);
	FOR(i, 2, n) {
		int p = prime_div[i];
		ans[i] = ans[i / p] * (p - bool(i / p % p));
	}
	return ans;
} // END HASH
