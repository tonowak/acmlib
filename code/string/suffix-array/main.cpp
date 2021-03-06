/*
 * Opis: Tablica suffixowa
 * Status: Cośtam potestowany
 * Czas: O(n \log n)
 * Użycie: SuffixArray t(s, lim) - lim to rozmiar alfabetu
 * sa zawiera posortowane suffixy, zawiera pusty suffix
 * lcp[i] to lcp suffixu sa[i - 1] i sa[i]
 * Dla s = "aabaaab" sa = {6, 3, 0, 4, 1, 5, 2}, lcp = {0, 0, 3, 1, 2, 0, 1}
 */

struct SuffixArray {
	vector<int> sa, lcp;
	SuffixArray(string& s, int lim = 256) { // lub basic_string<int>
		int n = ssize(s) + 1, k = 0, a, b;
		vector<int> x(s.begin(), s.end() + 1);
		vector<int> y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y;
		iota(sa.begin(), sa.end(), 0);

		for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j;
			iota(y.begin(), y.end(), n - j);
			REP(i, n) if(sa[i] >= j)
				y[p++] = sa[i] - j;
			fill(ws.begin(), ws.end(), 0);
			REP(i, n) ws[x[i]]++;
			FOR(i, 1, lim - 1) ws[i] += ws[i - 1];
			for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1, x[sa[0]] = 0;
			FOR(i, 1, n - 1) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		FOR(i, 1, n - 1) rank[sa[i]] = i;
		for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for(k && k--, j = sa[rank[i] - 1];
				s[i + k] == s[j + k]; k++);
	}
};
