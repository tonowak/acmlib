/*
 * Opis: FWHT
 * Czas: O(n \log n)
 * Pamięć : O(1)
 * Użycie:
 *   n musi być potęgą dwójki.
 *
 *   fwht_or(a)[i] = suma(j będące podmaską i) a[j].
 *   ifwht_or(fwht_or(a)) == a.
 *   convolution_or(a, b)[i] = suma(j | k == i) a[j] * b[k].
 *
 *   fwht_and(a)[i] = suma(j będące nadmaską i) a[j].
 *   ifwht_and(fwht_and(a)) == a.
 *   convolution_and(a, b)[i] = suma(j & k == i) a[j] * b[k].
 *
 *   fwht_xor(a)[i] = suma(j oraz i mają parzyście wspólnie zapalonych bitów) a[j] - suma(j oraz i mają nieparzyście) a[j].
 *   ifwht_xor(fwht_xor(a)) == a.
 *   convolution_xor(a, b)[i] = suma(j ^ k == i) a[j] * b[k].
 */

vector<int> fwht_or(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = 1; 2 * s <= n; s *= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i + s] += a[i];
	return a;
}
vector<int> ifwht_or(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = n / 2; s >= 1; s /= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i + s] -= a[i];
	return a;
}
vector<int> convolution_or(vector<int> a, vector<int> b) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0 and ssize(b) == n);
	a = fwht_or(a);
	b = fwht_or(b);
	REP(i, n)
		a[i] *= b[i];
	return ifwht_or(a);
}

vector<int> fwht_and(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = 1; 2 * s <= n; s *= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i] += a[i + s];
	return a;
}
vector<int> ifwht_and(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = n / 2; s >= 1; s /= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i)
				a[i] -= a[i + s];
	return a;
}
vector<int> convolution_and(vector<int> a, vector<int> b) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0 and ssize(b) == n);
	a = fwht_and(a);
	b = fwht_and(b);
	REP(i, n)
		a[i] *= b[i];
	return ifwht_and(a);
}

vector<int> fwht_xor(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = 1; 2 * s <= n; s *= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i) {
				int t = a[i + s];
				a[i + s] = a[i] - t;
				a[i] += t;
			}
	return a;
}
vector<int> ifwht_xor(vector<int> a) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0);
	for(int s = n / 2; s >= 1; s /= 2)
		for(int l = 0; l < n; l += 2 * s)
			for(int i = l; i < l + s; ++i) {
				int t = a[i + s];
				a[i + s] = (a[i] - t) / 2;
				a[i] = (a[i] + t) / 2;
			}
	return a;
}
vector<int> convolution_xor(vector<int> a, vector<int> b) {
	int n = ssize(a);
	assert((n & (n - 1)) == 0 and ssize(b) == n);
	a = fwht_xor(a);
	b = fwht_xor(b);
	REP(i, n)
		a[i] *= b[i];
	return ifwht_xor(a);
}

