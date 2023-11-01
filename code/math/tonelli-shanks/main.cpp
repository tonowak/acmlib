/*
 * Opis: O(\log^2(p))), dla pierwszego $p$ oraz $0 \le a \le p - 1$ znajduje takie $x$,
 * że $x^2 \equiv a \pmod{p}$ lub $-1$ jeżeli takie $x$ nie istnieje, można przepisać by działało dla LL
 */
int mul(int a, int b, int p) {
	return int(a * LL(b) % p);
}
int powi(int a, int b, int p) {
	for (int ret = 1;; b /= 2) {
		if (!b) return ret;
		if (b & 1) ret = mul(ret, a, p);
		a = mul(a, a, p);
	}
}
int tonelli_shanks(int a, int p) {
	if (a == 0) return 0;
	if (p == 2) return 1;
	if (powi(a, p / 2, p) != 1) return -1;
	int q = p - 1, s = 0, z = 2;
	while (q % 2 == 0) q /= 2, ++s;
	while (powi(z, p / 2, p) == 1) ++z;
	int c = powi(z, q, p), t = powi(a, q, p);
	int r = powi(a, q / 2 + 1, p);
	while (t != 1) {
		int i = 0, x = t;
		while (x != 1) x = mul(x, x, p), ++i;
		c = powi(c, 1 << (s - i - 1), p); // 1ll dla LL
		r = mul(r, c, p), c = mul(c, c, p);
		t = mul(t, c, p), s = i;
	}
	return r;
}
