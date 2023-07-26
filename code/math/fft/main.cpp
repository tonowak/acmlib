/*
 * Opis: O(n\log n), \texttt{conv(a, b)} to iloczyn wielomianów.
 */
using Complex = complex<double>;
void fft(vector<Complex> &a) {
	int n = ssize(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<Complex> rt(2, 1);
	for(static int k = 2; k < n; k *= 2) {
		R.resize(n), rt.resize(n);
		auto x = polar(1.0L, acosl(-1) / k);
		FOR(i, k, 2 * k - 1)
			rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
	vector<int> rev(n);
	REP(i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	REP(i, n) if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int k = 1; k < n; k *= 2) {
		for(int i = 0; i < n; i += 2 * k) REP(j, k) {
			Complex z = rt[j + k] * a[i + j + k]; // mozna zoptowac rozpisujac
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
	}
}
vector<double> conv(vector<double> &a, vector<double> &b) {
	if(a.empty() || b.empty()) return {};
	vector<double> res(ssize(a) + ssize(b) - 1);
	int L = 32 - __builtin_clz(ssize(res)), n = (1 << L);
	vector<Complex> in(n), out(n);
	copy(a.begin(), a.end(), in.begin());
	REP(i, ssize(b)) in[i].imag(b[i]);
	fft(in);
	for(auto &x : in) x *= x;
	REP(i, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	REP(i, ssize(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
