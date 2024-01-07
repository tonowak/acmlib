/*
 * Opis: O(n \log n),
 *   $n$ musi być potęgą dwójki,
 *   \texttt{fwht\_or(a)[i] = suma(j będące podmaską i) a[j]},
 *   \texttt{ifwht\_or(fwht\_or(a)) == a},
 *   \texttt{convolution\_or(a, b)[i] = suma(j | k == i) a[j] * b[k]},
 *   \texttt{fwht\_and(a)[i] = suma(j będące nadmaską i) a[j]},
 *   \texttt{ifwht\_and(fwht\_and(a)) == a},
 *   \texttt{convolution\_and(a, b)[i] = suma(j \& k == i) a[j] * b[k]},
 *   \texttt{fwht\_xor(a)[i] = suma(j oraz i mają parzyście wspólnie zapalonych bitów) a[j] - suma(j oraz i mają nieparzyście) a[j]},
 *   \texttt{ifwht\_xor(fwht\_xor(a)) == a},
 *   \texttt{convolution\_xor(a, b)[i] = suma(j \^ k == i) a[j] * b[k]}.
 */

#include "../simple-modulo/main.cpp"

// BEGIN HASH
using T = array<array<int, 2>, 2>;
void kronecker(vector<int> &a, T mt) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for (int s = 1; 2 * s <= n; s *= 2)
		for (int l = 0; l < n; l += 2 * s)
			for (int i = l; i < l + s; ++i) {
				int val = a[i];
				a[i] = add(mul(a[i], mt[0][0]), mul(a[i + s], mt[0][1]));
				a[i + s] = add(mul(val, mt[1][0]), mul(a[i + s], mt[1][1]));
			}
} // END HASH
// BEGIN HASH
vector<int> kronecker_convolution(vector<int> a, vector<int> b, T mt, T rev) {
	int n = ssize(a);
	assert(ssize(b) == n);
	kronecker(a, mt);
	kronecker(b, mt);
	REP (i, n)
		a[i] = mul(a[i], b[i]);
	kronecker(a, rev);
	return a;
} // END HASH
// BEGIN HASH
vector<int> convolution_or(vector<int> a, vector<int> b) {
	return kronecker_convolution(a, b,
			T{{{1, 0}, {1, 1}}},
			T{{{1, 0}, {mod - 1, 1}}});
} // END HASH
// BEGIN HASH
vector<int> convolution_and(vector<int> a, vector<int> b) {
	return kronecker_convolution(a, b,
			T{{{1, 1}, {0, 1}}},
			T{{{1, mod - 1}, {0, 1}}});
} // END HASH
// BEGIN HASH
vector<int> convolution_xor(vector<int> a, vector<int> b) {
	const int rev2 = (mod + 1) / 2;
	return kronecker_convolution(a, b,
			T{{{1, 1}, {1, mod - 1}}},
			T{{{rev2, rev2}, {rev2, mod - rev2}}});
} // END HASH
