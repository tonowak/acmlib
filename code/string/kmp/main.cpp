/*
 * Opis: O(n),
 *   zachodzi [0, pi[i]) = (i - pi[i], i].
 *   \texttt{get\_kmp(\{0,1,0,0,1,0,1,0,0,1\}) == \{0,0,1,1,2,3,2,3,4,5\}},
 *   \texttt{get\_borders(\{0,1,0,0,1,0,1,0,0,1\}) == \{2,5,10\}}.
 */

vector<int> get_kmp(vector<int> str) {
	int len = ssize(str);
	vector<int> ret(len);
	for(int i = 1; i < len; i++) {
		int pos = ret[i - 1];
		while(pos and str[i] != str[pos])
			pos = ret[pos - 1];
		ret[i] = pos + (str[i] == str[pos]);
	}
	return ret;
}

vector<int> get_borders(vector<int> str) {
	vector<int> kmp = get_kmp(str), ret;
	int len = ssize(str);
	while(len) {
		ret.emplace_back(len);
		len = kmp[len - 1];
	}
	return vector<int>(ret.rbegin(), ret.rend());
}
