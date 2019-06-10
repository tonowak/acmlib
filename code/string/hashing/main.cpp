// Haszowanie
// Autor : Michał Staniewski
// Status : Nieprzetestowane
// get_hash(l, r) zwraca hash przedziału [l, r]
// baza jest randomowa, żeby nie zostać zhackowanym

struct Hashing
{
	vector<LL> ha, pw;
	LL mod = 1000696969;
	int base;

	Hashing(string &str) {
		base = rd(30, 50);
		int len = size(str);
		ha.resize(len + 1);
		pw.resize(len + 1);
		REP(i, len) {
			ha[i + 1] = (ha[i] * base + str[i] - 'a' + 1) % mod;
			pw[i + 1] = (pw[i] * base) % mod;
		}
	}

	LL get_hash(int l, int r) {
		return ((ha[r + 1] - ha[l] * pw[r - a]) % mod + mod) % mod;
	}
};
