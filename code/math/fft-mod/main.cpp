/*
 * Opis: O(n \log n),
 *   \texttt{conv\_mod(a, b)} zwraca iloczyn wielomianów modulo, ma większą dokładność niż zwykłe fft.
 */
#include "../fft/main.cpp"
vector<int> conv_mod(vector<int> a, vector<int> b, int M) {
	if(a.empty() or b.empty()) return {};
	vector<int> res(ssize(a) + ssize(b) - 1);
	const int CUTOFF = 125;
	if (min(ssize(a), ssize(b)) <= CUTOFF) {
		if (ssize(a) > ssize(b))
			swap(a, b);
		REP (i, ssize(a))
			REP (j, ssize(b))
				res[i + j] = int((res[i + j] + LL(a[i]) * b[j]) % M);
		return res;
	}
	int B = 32 - __builtin_clz(ssize(res)), n = 1 << B;
	int cut = int(sqrt(M));
	vector<Complex> L(n), R(n), outl(n), outs(n);
	REP(i, ssize(a)) L[i] = Complex((int) a[i] / cut, (int) a[i] % cut);
	REP(i, ssize(b)) R[i] = Complex((int) b[i] / cut, (int) b[i] % cut);
	fft(L), fft(R);
	REP(i, n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	REP(i, ssize(res)) {
		LL av = LL(real(outl[i]) + 0.5), cv = LL(imag(outs[i]) + 0.5);
		LL bv = LL(imag(outl[i]) + 0.5) + LL(real(outs[i]) + 0.5);
		res[i] = int(((av % M * cut + bv) % M * cut + cv) % M);
	}
	return res;
}
