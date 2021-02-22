/*
 * Status: Przetestowane
 * Opis: KMP(str) zwraca tablicę pi.
 * [0, pi[i]) = (i - pi[i], i]
 * Czas: O(n)
 */

vector<int> KMP(string &str) {
	int len = ssize(str);
	vector<int> ret(len);
	for(int i = 1; i < len; i++)
	{
		int pos = ret[i - 1];
		while(pos && str[i] != str[pos]) pos = ret[pos - 1];
		ret[i] = pos + (str[i] == str[pos]);
	}
	return ret;
}
