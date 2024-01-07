/*
 * Opis: O(n \log n),
 *   $n$ musi być potęgą dwójki,
 *   \texttt{convolution\_or(a, b)[i] = suma(j | k == i) a[j] * b[k]},
 *   \texttt{convolution\_and(a, b)[i] = suma(j \& k == i) a[j] * b[k]},
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
template<int t00, int t01, int t10, int t11>
void other_kronecker(vector<int> &a, integer_sequence<int, t00, t01, t10, t11>) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for (int s = 1; 2 * s <= n; s *= 2)
		for (int l = 0; l < n; l += 2 * s)
			for (int i = l; i < l + s; ++i) {
				int val = a[i];
				a[i] = add(mul(a[i], t00), mul(a[i + s], t01));
				a[i + s] = add(mul(val, t10), mul(a[i + s], t11));
			}
}
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
template<int t00, int t01, int t10, int t11, int r00, int r01, int r10, int r11>
vector<int> other_kronecker_convolution(vector<int> a, vector<int> b,
		integer_sequence<int, t00, t01, t10, t11> s1,
		integer_sequence<int, r00, r01, r10, r11> s2) {
	int n = ssize(a);
	assert(ssize(b) == n);
	other_kronecker(a, s1);
	other_kronecker(b, s1);
	REP (i, n)
		a[i] = mul(a[i], b[i]);
	other_kronecker(a, s2);
	return a;
}
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
	constexpr int rev2 = (mod + 1) / 2;
	auto ret = other_kronecker_convolution(a, b,
			integer_sequence<int, 1, 1, 1, mod - 1>{},
			integer_sequence<int, 1, 1, 1, mod - 1>{});
	int n = ssize(a);
	assert(n);
	int revn = 1;
	REP (i, __lg(n))
		revn = mul(revn, rev2);
	for (auto &i : a)
		i = mul(i, revn);
	return a;
	/*
	return kronecker_convolution(a, b,
			T{{{1, 1}, {1, mod - 1}}},
			T{{{rev2, rev2}, {rev2, mod - rev2}}});
			*/
} // END HASH
