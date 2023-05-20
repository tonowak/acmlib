/*
 * Opis: Wyznacza przedziały o takiej samej wartości $\lfloor n / x\rfloor$ lub $\lceil n / x\rceil$.
 * Czas: O(\sqrt{n})
 * Użycie:
 *  auto a = same_floor(n); auto b = same_ceil(n);
 *  same_floor(8) = {(1, 1), (2, 2), (3, 4), (5, 8)}
 *  same_ceil(8) = {(8, 8), (4, 7), (3, 3), (2, 2), (1, 1)}
 *  Na konteście raczej checemy przepisać tylko pętlę i od razu wykonywać obliczenia na parze (l, r) zamiast grupować wszyskie przedziały w vectorze.
 *  Dla n będącego intem można zmienić wszystkie LL na int, w celu zbicia stałej.
 */

vector<pair<LL, LL>> same_floor(LL n) {
	vector<pair<LL, LL>> v;
	for (LL l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		v.emplace_back(l, r);
	}
	return v;
}

vector<pair<LL, LL>> same_ceil(LL n) {
	vector<pair<LL, LL>> v;
	for (LL r = n, l; r >= 1; r = l - 1) {
		l = (n + r - 1) / r;
		l = (n + l - 1) / l;
		v.emplace_back(l, r);
	}
	return v;
}
