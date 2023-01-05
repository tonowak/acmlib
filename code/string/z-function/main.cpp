/*
 * Opis: get_z_function(str) zwraca funkcję Z, tzn. tablicę pref-pref.
 * Zachodzi [0, z[i]) = [i, i + z[i]).
 * Czas: O(n)
 * Użycie:
 *   get_z_function({0,1,0,0,1,0,1,0,0,1}) == {10,0,1,3,0,5,0,1,2,0}
 */

vector<int> get_z_function(vector<int> s) {
	int n = ssize(s);
	vector<int> z(n);
	for(int i = 1, l = 0, r = 0; i < n; ++i) {
		if(i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while(i + z[i] < n and s[z[i]] == s[i + z[i]])
			++z[i];
		if(i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	z[0] = n;
	return z;
}
