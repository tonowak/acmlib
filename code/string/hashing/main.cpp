/*
 * Status: Przetestowane
 * Opis: Haszowanie
 * Czas: O(1)
 * Użycie:
 * get_hash(l, r) zwraca hasza [l, r] włącznie
 * można zmienić modulo i bazę
 */

struct Hashing
{
	vector<LL> ha, pw;
	LL mod = 1000696969;
	int base;

	Hashing(string &str) {
		base = rd(30, 50);
		int len = size(str);
		ha.resize(len + 1);
		pw.resize(len + 1, 1);
		REP(i, len) {
			ha[i + 1] = (ha[i] * base + str[i] - 'a' + 1) % mod;
			pw[i + 1] = (pw[i] * base) % mod;
		}
	}

	LL get_hash(int l, int r) {
		return ((ha[r + 1] - ha[l] * pw[r - l + 1]) % mod + mod) % mod;
	}
};
