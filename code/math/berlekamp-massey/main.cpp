/*
 * Opis: Zgadywanie rekurencji liniowej
 * Status: Chyba działa xd
 * Czas: O(n^2 \log k)
 * Pamięć : O(n)
 * Użycie:
 *   Berlekamp_Massey<mod> bm(x) zgaduje rekurencję ciągu x
 *   bm.get(k) zwraca k-ty wyraz ciągu x (index 0)
 */

template<int mod>
struct BerlekampMassey {
	int mul(int a, int b) {
		return (LL) a * b % mod;
	}
	int add(int a, int b) {
		return a + b < mod ? a + b : a + b - mod;
	}
	int qpow(int a, int b) {
		if(b == 0) return 1;
		if(b % 2 == 1) return mul(qpow(a, b - 1), a);
		return qpow(mul(a, a), b / 2);
	}

	int n;
	vector<int> x, C;
	BerlekampMassey(vector<int> &_x) : x(_x) {
		vector<int> B; B = C = {1};
		int b = 1, m = 0;
		REP(i, ssize(x)) { 
			m++; int d = x[i];
			FOR(j, 1, ssize(C) - 1)
				d = add(d, mul(C[j], x[i - j]));
			if(d == 0) continue;
			auto _B = C; 
			C.resize(max(ssize(C), m + ssize(B)));
			int coef = mul(d, qpow(b, mod - 2));
			FOR(j, m, m + ssize(B) - 1) 
				C[j] = (C[j] - mul(coef, B[j - m]) + mod) % mod;
			if(ssize(_B) < m + ssize(B)) { B = _B; b = d; m = 0; }
		}
		C.erase(C.begin());
		for(int &t : C) t = add(mod, -t);
		n = ssize(C);
	}

	vector<int> combine(vector<int> a, vector<int> b) {
		vector<int> ret(n * 2 + 1);
		REP(i, n + 1) REP(j, n + 1)
			ret[i + j] = add(ret[i + j], mul(a[i], b[j]));
		for(int i = 2 * n; i > n; i--) REP(j, n)
			ret[i - j - 1] = add(ret[i - j - 1], mul(ret[i], C[j]));
		return ret;
	}

	int get(LL k) {
		vector<int> r(n + 1), pw(n + 1);
		r[0] = pw[1] = 1;
		for(k++; k; k /= 2) {
			if(k % 2) r= combine(r, pw);
			pw = combine(pw, pw);
		}
		LL ret = 0;
		REP(i, n) ret = add(ret, mul(r[i + 1], x[i]));
		return ret;
	}
};
