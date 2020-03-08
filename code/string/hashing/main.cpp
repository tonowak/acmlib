/*
 * Status: Przetestowane
 * Opis:
 * Użycie: 
 * Hashing hsh(str);
 * hsh(l, r) zwraca hasza [l, r] włącznie
 * można zmienić modulo i bazę
 * Czas: O(1)
 */

struct Hashing {
	vector<int> ha, pw;
	int mod = 1e9 + 696969;
	int base;

	Hashing(string &str, int b = -1) {
		if(b == -1) base = rd(30, 50);
		else base = b;

		int len = size(str);
		ha.resize(len + 1);
		pw.resize(len + 1, 1);
		REP(i, len) {
			ha[i + 1] = ((LL) ha[i] * base + str[i] - 'a' + 1) % mod;
			pw[i + 1] = ((LL) pw[i] * base) % mod;
		}
	}

	int operator()(int l, int r) {
		return (((LL) ha[r + 1] - ha[l] * pw[r - l + 1]) % mod + mod) % mod;
	}
};
