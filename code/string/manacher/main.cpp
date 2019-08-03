/*
 * Opis: radius[p][i] = $rad$ = największy promień palindromu
 *   parzystości p o środku i. $L=i-rad+!p, \; R=i+rad$ to palindrom.
 *   Dla [abaababaab] daje [003000020], [0100141000].
 * Czas: O(n)
 */

array<vector<int>, 2> manacher(vector<int> &in) {
	int n = size(in);
	array<vector<int>, 2> radius = {{vector<int>(n - 1), vector<int>(n)}};
	REP(parity, 2) {
		int z = parity ^ 1, L = 0, R = 0;
		REP(i, n - z) {
			int &rad = radius[parity][i];
			if(i <= R - z)
				rad = min(R - i, radius[parity][L + (R - i - z)]);
			int l = i - rad + z, r = i + rad;
			while(0 <= l - 1 && r + 1 < n && in[l - 1] == in[r + 1])
				++rad, ++r, --l;
			debug(i, rad, l, r);
			if(r > R)
				L = l, R = r;
		}
	}
	return radius;
}
