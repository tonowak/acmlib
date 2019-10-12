/*
 * Opis: Drzewo przedział-przedział
 * Czas: O(\log^2_n)
 * Pamięć : O(1)
 * Użycie:
 *   Miller_Rabin(n) zwraca, czy n jest pierwsze
 *   działa dla long longów
 */

LL mul(LL a, LL b, LL mod) {
	return (a * b - (LL)((long double) a * b / mod) * mod + mod) % mod;
}

LL fpow(LL a, LL n, LL mod)
{
	if(n == 0) return 1;
	if(n % 2 == 1) return mul(fpow(a, n - 1, mod), a, mod);
	LL ret = fpow(a, n / 2, mod);
	return mul(ret, ret, mod);
}

bool Miller_Rabin(LL n) {
	if(n < 2) return false;

	int r = 0;
	LL d = n - 1;
	while(d % 2 == 0)
		d /= 2, r++;

	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}) {
		if(n == a) return true;
		LL x = fpow(a, d, n);
		if(x == 1 || x == n - 1)
			continue;

		bool composite = true;
		REP(i, r - 1) {
			x = mul(x, x, n);
			if(x == n - 1) {
				composite = false;
				break;
			}
		}
		if(composite) return false;
	}

	return true;
}
