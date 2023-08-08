/*
 * Opis: Generatorka wielokątów wypukłych.
 * Przyjmuje n, zakres i wielokąt ma być ściśle wypukły (domyślnie nie).
 * Zwraca wielokąt mniejszy o maksymalnie DEC% punktów w zakresie [-range, range].
 * Nieścisłe zwraca zawsze rozmiaru n.
 */
#include "../point/main.cpp"
#include "../angle-sort/main.cpp"
#include "../../headers/gen.cpp"
vector<int> num_split(int value, int n) {
	vector<int> v(n, value);
	REP(i, n - 1)
		v[i] = rd(0, value);
	sort(v.begin(), v.end());
	adjacent_difference(v.begin(), v.end(), v.begin());
	return v;
}
vector<int> capped_zero_split(int cap, int n) {
	int m = rd(1, n - 1);
	auto lf = num_split(cap, m);
	auto rg = num_split(cap, n - m);
	for (int i : rg)
		lf.emplace_back(-i);
	return lf;
}
vector<P> gen_convex_polygon(int n, int range, bool strictly_convex = false) {
	assert(n > 2);
	vector<P> t;
	const double DEC = 0.1;
	do {
		t.clear();
		auto dx = capped_zero_split(range, n);
		auto dy = capped_zero_split(range, n);
		shuffle(dx.begin(), dx.end(), rng);
		REP (i, n)
			if (dx[i] || dy[i])
				t.emplace_back(dx[i], dy[i]);
		t = angle_sort(t);
		if (strictly_convex) {
			vector<P> nt;
			nt.emplace_back(t[0]);
			FOR (i, 1, ssize(t) - 1) {
				if (!sign(cross(t[i], nt.back())))
					nt.back() += t[i];
				else
					nt.emplace_back(t[i]);
			}
			while (!nt.empty() && !sign(cross(nt.back(), nt[0]))) {
				nt[0] += nt.back();
				nt.pop_back();
			}
			t = nt;
		}
	} while (ssize(t) * (1 + DEC) < n);
	partial_sum(t.begin(), t.end(), t.begin());
	return t;
}
