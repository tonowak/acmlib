/*
 * Status: Przetestowane
 * Opis: pref(str) zwraca tablicę prefixo prefixową
 * [0, pref[i]) = [i, i + pref[i])
 * Czas: O(n)
 */

vector<int> pref(string &str) {
	int len = ssize(str);	
	vector<int> ret(len);
	ret[0] = len;
	int i = 1, m = 0;
	while(i < len) {
		while(m + i < len && str[m + i] == str[m]) m++;
		ret[i++] = m;
		m = (m != 0 ? m - 1 : 0);
		for(int j = 1; ret[j] < m; m--) ret[i++] = ret[j++];
	}
	return ret;
}
