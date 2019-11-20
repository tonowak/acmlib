/*
 * Opis: FFT
 * Status: Chyba działa xd
 * Czas: O(n \log n)
 * Użycie:
 *   conv(a, b) zwraca iloczyn wielomianów a i b
 *   conv_int(a, b) robi to samo, tyle że wykorzystując inty
 */

using Complex = complex<double>;
void fft(vector<Complex> &a) {
	int n = size(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<Complex> rt(2, 1);
	for(static int k = 2; k < n; k *= 2) {
		R.resize(n), rt.resize(n);
		auto x = polar(1.0L, M_PIl / k);
		FOR(i, k, 2 * k - 1) 
			rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}

	vector<int> rev(n);
	REP(i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	REP(i, n) if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int k = 1; k < n; k *= 2) {
		for(int i = 0; i < n; i += 2 * k) REP(j, k) {
			auto x = (double *) &rt[j + k], y = (double *) &a[i + j + k];
			Complex z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
	}
}

vector<double> conv(vector<double> &a, vector<double> &b) {
	if(a.empty() || b.empty()) return {};
	vector<double> res(size(a) + size(b) - 1);
	int L = 32 - __builtin_clz(size(res)), n = (1 << L);
	vector<Complex> in(n), out(n);
	copy(a.begin(), a.end(), in.begin());
	REP(i, size(b)) in[i].imag(b[i]);
	fft(in);
	for(auto &x : in) x *= x;
	REP(i, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	REP(i, size(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

vector<double> to_doubles(vector<int> &v) {
	int n = size(v);
	vector<double> ret(n);
	REP(i, n) ret[i] = v[i];
	return ret;
}

vector<int> conv_int(vector<int> &a, vector<int> &b) {
	auto A = to_doubles(a), B = to_doubles(b);
	auto res = conv(A, B);
	int n = size(res);
	vector<int> ans(n);
	REP(i, n) ans[i] = round(res[i]);
	return ans;
}
