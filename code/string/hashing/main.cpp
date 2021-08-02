/*
 * Status: Przetestowane
 * Opis:
 * Użycie: 
 * Hashing hsh(str);
 * hsh(l, r) zwraca hasza [l, r] włącznie
 * można zmienić modulo i bazę
 * Czas: O(1)
 */
#include "../../random-stuff/rd/main.cpp"

struct Hashing {
	vector<int> ha, pw;
	int mod = 1e9 + 696969;
	int base;

	Hashing(string &str, int b) {
		base = b;
		int len = ssize(str);
		ha.resize(len + 1);
		pw.resize(len + 1, 1);
		REP(i, len) {
			ha[i + 1] = int(((LL) ha[i] * base + str[i] - 'a' + 1) % mod);
			pw[i + 1] = int(((LL) pw[i] * base) % mod);
		}
	}

	int operator()(int l, int r) {
		return int(((ha[r + 1] - (LL) ha[l] * pw[r - l + 1]) % mod + mod) % mod);
	}
};

struct DoubleHashing {
	Hashing h1, h2;
	DoubleHashing(string &str) : h1(str, 31), h2(str, 33) {} // change to rd on codeforces
	LL operator()(int l, int r) {
		return h1(l, r) * LL(h2.mod) + h2(l, r);
	}
};
