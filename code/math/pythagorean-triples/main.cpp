/*
 * Opis: Wyznacza wszystkie trójki $(a, b, c)$ takie, że $a^2+b^2=c^2$, $gcd(a, b, c) = 1 oraz $c \leq \text{limit}$. Zwraca tylko jedną z $(a, b, c)$ oraz $(b, a, c)$.
 */
vector<tuple<int, int, int>> pythagorean_triples(int limit) {
	vector<tuple<int, int, int>> ret;
	function<void(int, int, int)> gen = [&](int a, int b, int c) {
		if (c > limit)
			return;
		ret.emplace_back(a, b, c);
		REP(i, 3) {
			gen(a + 2 * b + 2 * c, 2 * a + b + 2 * c, 2 * a + 2 * b + 3 * c);
			a = -a;
			if (i) b = -b;
		}
	};
	gen(3, 4, 5);
	return ret;
}
