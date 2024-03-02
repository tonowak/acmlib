/*
 * Opis: Generatorka wielokątów niekoniecznie-wypukłych.
 * Zwraca wielokąt z o $n$ punktach w zakresie $[-\texttt{r}, \texttt{r}]$,
 * który nie zawiera jakiejkolwiek trójki współliniowych punktów.
 * Ciągnie do ~80. Dla $n < 3$ zwraca zdegenerowane.
 */
#include "../point/main.cpp"
#include "../intersect-lines/main.cpp"
#include "../../headers/gen.cpp"
vector<P> gen_polygon(int n, int r) {
	vector<P> t;
	while (ssize(t) < n) {
		P p(rd(-r, r), rd(-r, r));
		if ([&]() {
			REP (i, ssize(t))
				REP (j, i)
					if (dir(t[i], t[j], p) == 0)
						return false;
			return find(t.begin(), t.end(), p) == t.end();
		}())
			t.emplace_back(p);
	}
	bool go = true;
	while (go) {
		go = false;
		REP (i, n)
			REP (j, i - 1)
				if ((i + 1) % n != j && ssize(intersect_segments(t[i], t[(i + 1) % n], t[j], t[j + 1]))) {
					swap(t[(i + rd(0, 1)) % n], t[(j + rd(0, 1)) % n]);
					go = true;
				}
	}
	return t;
}
