/*
 * Status: Przetestowane
 * Opis: Drzewo potęgowe
 * Czas: O(\log n)
 * Użycie:
 *   wszystko indexowane od 0
 *   update(pos, val) dodaje val do elementu pos
 *   query(pos) zwraca sumę na przedziale [0, pos]
 */

struct Fenwick {
	vector<LL> s;
	Fenwick(int n) : s(n) {}
	void update(int pos, LL val) {
		for(; pos < ssize(s); pos |= pos + 1)
			s[pos] += val;
	}
	LL query(int pos) {
		LL ret = 0;
		for(pos++; pos > 0; pos &= pos - 1)
			ret += s[pos - 1];
		return ret;
	}
};
