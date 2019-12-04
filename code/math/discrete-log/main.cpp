/*
 * Opis: Dla liczby pierwszej $p$ oraz $a, b \nmid p$
 * znajdzie $e$ takie że $a^e \equiv b \pmod{p}$
 * Czas: O(\sqrt{n} \log n)
 * Pamięć: O(\sqrt{n})
*/

int discrete_log(int a, int b, int p) {
	map<int, int> s1;
	LL mult = 1, sq = sqrt(p);
	REP(i, sq) {
		s1[mult] = i; mult = mult * a % p;
	}
	int t = 1;
	debug(s1, t);
	REP(i, sq + 2) {
		int inv = b * exp(t, p - 2, p) % p;
		if(s1.count(inv)) return i * sq + s1[inv];
		t = t * mult % p;
	}
	return -1;
}
	
