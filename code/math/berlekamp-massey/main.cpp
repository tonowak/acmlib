/*
 * Opis: Berlekamp-Massey
 * Status: Chyba działa xd
 * Czas: O(n^2 \log k)
 * Pamięć : O(n)
 * Użycie:
 *   Berlekamp_Massey(x) zgaduje rekurencję liniową ciagu x
 *   get_kth(x, rec, k) zwraca k-ty ciągu x o rekurencji rec
 */

int mod = 1000696969;

LL fpow(LL a, LL n) {
	if(n == 0) return 1;
	if(n % 2 == 1) return fpow(a, n - 1) * a % mod;
	LL r = fpow(a, n / 2);
	return r * r % mod;
}

vector<LL> Berlekamp_Massey(vector<LL> x) {
	vector<LL> cur, ls;
	LL lf = 0, ld = 0;

	for(int i = 0; i < x.size(); i++) {
		LL t = 0;
		for(int j = 0; j < cur.size(); j++)
			t = (t + x[i - 1 - j] * cur[j]) % mod;

		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()) {
			cur.resize(i + 1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}

		LL k = (t - x[i]) * fpow(ld, mod - 2) % mod;
		vector<LL> c(i - lf - 1);
		c.emplace_back(k);
		for(int j = 0; j < ls.size(); j++)
			c.emplace_back(- k * ls[j] % mod);

		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j = 0; j < cur.size(); j++)
			c[j] = (c[j] + cur[j]) % mod;

		if(i - lf + (int)ls.size() >= (int)cur.size())
			ls = cur, lf = i, ld = (t - x[i]);

		cur = c;		
	}

	for(LL &val : cur) val = (val % mod + mod) % mod;
	return cur;
}

LL get_kth(vector<LL> x, vector<LL> rec, LL k) {
	int n = size(rec);
	auto combine = [&](vector<LL> a, vector<LL> b) {
		vector<LL> ret(n * 2 + 1);
		REP(i, n + 1) REP(j, n + 1)
			ret[i + j] = (ret[i + j] + a[i] * b[j]) % mod;
		for(int i = 2 * n; i > n; i--) REP(j, n)
			ret[i - j - 1] = (ret[i - j - 1] + ret[i] * rec[j]) % mod;
		ret.resize(n + 1);
		return ret;
	};

	vector<LL> r(n + 1), pw(n + 1);
	r[0] = 1, pw[1] = 1;

	for(++k; k; k /= 2) {
		if(k % 2) r = combine(r, pw);
		pw = combine(pw, pw);
	}

	LL ret = 0;
	REP(i, n) ret = (ret + r[i + 1] * x[i]) % mod;
	return ret;
}
