/*
 * Opis: Test pierwszości Millera-Rabina
 * Czas: O(\log^2n)
 * Pamięć : O(1)
 * Użycie:
 *   miller_rabin(n) zwraca czy n jest pierwsze
 *   działa dla long longów
 */

LL llmul(LL a, LL b, LL m) {
	return (a * b - (LL)((long double) a * b / m) * m + m) % m;
}

LL llpowi(LL a, LL n, LL m) {
	if(n == 0) return 1;
	if(n % 2 == 1) return llmul(llpowi(a, n - 1, m), a, m);
	return llpowi(llmul(a, a, m), n / 2, m);
}

bool miller_rabin(LL n) {
	if(n < 2) return false;
	int r = 0;
	LL d = n - 1;
	while(d % 2 == 0)
		d /= 2, r++;
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
		if(n == a) return true;
		LL x = llpowi(a, d, n);
		if(x == 1 || x == n - 1)
			continue;
		bool composite = true;
		REP(i, r - 1) {
			x = llmul(x, x, n);
			if(x == n - 1) {
				composite = false;
				break;
			}
		}
		if(composite) return false;
	}
	return true;
}
