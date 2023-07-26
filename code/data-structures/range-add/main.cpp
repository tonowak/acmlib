/*
 * Opis: O(\log n) drzewo przedział-punkt $(+, +)$,
 *   wszystko indexowane od 0,
 *   \texttt{update(l, r, val)} dodaje val na przedziale $[l, r]$,
 *   \texttt{query(pos)} zwraca wartość elementu $pos$.
 */
#include "../fenwick-tree/main.cpp"
struct RangeAdd {
	Fenwick f;
	RangeAdd(int n) : f(n) {}
	void update(int l, int r, LL val) {
		f.update(l, val);
		f.update(r + 1, -val);
	}
	LL query(int pos) {
		return f.query(pos);
	}
};
