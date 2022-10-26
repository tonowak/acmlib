/*
 * Opis: Wyznaczanie faktoryzacji Lyndona oraz (przy jej pomocy) minimalnego suffixu oraz minimalnego przesunięcia cyklicznego. Ta faktoryzacja to unikalny podział słowa s na w1*w2*...*wk, że w1>=w2>=...>=wk oraz wi jest ściśle mniejsze od każdego jego suffixu.
 * Czas: O(n)
 * Użycie: duval("abacaba") == {{0, 3}, {4, 5}, {6, 6}};
 *   min_suffix("abacab") == "ab";
 *   min_cyclic_shift("abacaba") == "aabacab";
 */

vector<pair<int, int>> duval(vector<int> s) {
	int n = ssize(s), i = 0;
	vector<pair<int, int>> ret;
	while(i < n) {
		int j = i + 1, k = i;
		while(j < n and s[k] <= s[j]) {
			k = (s[k] < s[j] ? i : k + 1);
			++j;
		}
		while(i <= k) {
			ret.emplace_back(i, i + j - k - 1);
			i += j - k;
		}
	}
	return ret;
}

vector<int> min_suffix(vector<int> s) {
	return {s.begin() + duval(s).back().first, s.end()};
}

vector<int> min_cyclic_shift(vector<int> s) {
	int n = ssize(s);
	REP(i, n)
		s.emplace_back(s[i]);
	for(auto [l, r] : duval(s))
		if(n <= r) {
			return {s.begin() + l, s.begin() + l + n};
		}
	assert(false);
}

