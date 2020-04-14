/*
 * Status: Nieprzetestowane
 * Opis: Drzewo potęgowe
 * Czas: O(\log n)
 * Użycie:
 *   wszystko indexowane od 0
 *   update(pos, val) dodaje val do elementu pos
 *   query(pos) zwraca sumę na przedziale [0, pos)
 *   lower_bound(val) zwraca pos, że suma [0, pos] <= val, n jeśli nie istnieje, -1 jeśli puste
 */

struct Fenwick {
	vector<LL> s;
	Fenwick(int n) : s(n) {}
	void update(int pos, LL val) {
		for(; pos < size(s); pos |= pos + 1)
			s[pos] += val;
	}
	LL query(int pos) {
		LL ret = 0;
		for(; pos > 0; pos &= pos - 1)
			ret += s[pos - 1];
		return ret;
	}
};
