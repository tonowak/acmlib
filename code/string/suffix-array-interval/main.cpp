/*
 * Opis: O(t\log n), wyznaczanie przedziałów podsłowa w tablicy suffixowej.
 *   Zwraca przedział $[l, r]$, gdzie dla każdego $i$ w $[l, r]$, $t$ jest podsłowem $sa.sa[i]$
 *   lub $[-1, -1]$ jeżeli nie ma takiego $i$.
 */
#include "../suffix-array/main.cpp"

pair<int, int> get_substring_sa_range(const vector<int> &s, const SuffixArray &sa, const vector<int> &t) {
	auto get_lcp = [&](int i) -> int {
		REP(k, ssize(t))
			if(i + k >= ssize(s) or s[i + k] != t[k])
				return k;
		return ssize(t);
	};
	auto get_side = [&](bool search_left) {
		int l = 0, r = ssize(sa.sa) - 1;
		while(l < r) {
			int m = (l + r + not search_left) / 2, lcp = get_lcp(sa.sa[m]);
			if(lcp == ssize(t))
				(search_left ? r : l) = m;
			else if(sa.sa[m] + lcp >= ssize(s) or s[sa.sa[m] + lcp] < t[lcp])
				l = m + 1;
			else
				r = m - 1;
		}
		return l;
	};
	int l = get_side(true);
	if(get_lcp(sa.sa[l]) != ssize(t))
		return {-1, -1};
	return {l, get_side(false)};
}
