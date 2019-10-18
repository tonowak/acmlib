/*
 * Status: Przetestowane
 * Opis: KMP
 * Czas: O(n)
 * Użycie:
 * KMP(str) zwraca tablicę pi 
 */

vector<int> KMP(string &str) {
	int len = size(str);
	vector<int> ret(len);
	for(int i = 1; i < len; i++)
	{
		int pos = ret[i - 1];
		while(pos && str[i] != str[pos]) pos = ret[pos - 1];
		ret[i] = pos + (str[i] == str[pos]);
	}
	return ret;
}
