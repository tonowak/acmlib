// Pref
// Autor : Michał Staniewski
// Status : Nieprzetestowany
// [0, pref[i]) == [i, i + pref[i])

vector<int> pref(string &str) {
	int len = size(str);	
	vector<int> ret(len);
	ret[0] = len;
	int i = 1, m = 0;
	while(i < n) {
		while(m + i < n && str[m + i] == str[m]) m++;
		ret[i++] = m;
		m = (m != 0 ? m - 1 : 0);
		for(int j = 1; ret[j] < m; m--) p[i++] = p[j++];
	}
}
