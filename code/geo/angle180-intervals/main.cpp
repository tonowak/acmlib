/*
 * Opis: O(n),
 * ZAKŁADA że punkty są posortowane kątowo.
 * Zwraca $n$ par $[i, r]$, gdzie r jest maksymalnym
 * cyklicznie indeksem, że
 * wszystkie punkty w tym cyklicznym przedziale
 * są ściśle ,,po prawej''
 * stronie wektora $(0,0)-in[i]$, albo są na tej półprostej.
 */
#include "../angle-sort/main.cpp"
vector<pair<int, int>> angle180_intervals(vector<P> in) {
	// in must be sorted by angle
	int n = ssize(in);
	vector<int> nxt(n);
	iota(nxt.begin(), nxt.end(), 1);
	int r = nxt[n - 1] = 0;
	vector<pair<int, int>> ret(n);
	REP(l, n) {
		if(nxt[r] == l) r = nxt[r];
		auto good = [&](int i) {
			auto c = cross(in[l], in[i]);
			if(not equal(c, 0)) return c < 0;
			if((P(0, 0) < in[l]) != (P(0, 0) < in[i]))
				return false;
			return l < i;
		};
		while(nxt[r] != l and good(nxt[r]))
			r = nxt[r];
		ret[l] = {l, r};
	}
	return ret;
}
