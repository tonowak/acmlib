/*
 * Opis: Generatorka wielokątów wypukłych
 * Czas: O(n \log n)
 * Użycie:
 *
 */
#include "../point/main.cpp"
#include "../angle-sort/main.cpp"
#include "../../headers/gen.cpp"
D cross(P a, P b, P c) { return sign(cross(b - a, c - a)); }

vector<int> num_split(int value, int n) {
	vector<int> fence(n);
	fence[0] = 0;
	FOR (i, 1, n - 1)
		fence[i] = rd(0, value);
	fence.emplace_back(value);
	sort(fence.begin(), fence.end());
	vector<int> ret(n);
	FOR (i, 1, n)
		ret[i - 1] = fence[i] - fence[i - 1];
	return ret;
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
	do {
		t.clear();
		auto dx = capped_zero_split(range, n);
		auto dy = capped_zero_split(range, n);
		shuffle(dx.begin(), dx.end(), rng);
		REP (i, n)
			if (dx[i] || dy[i])
				t.emplace_back(P(dx[i], dy[i]));
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
	} while (ssize(t) * 1.1 < n);

	vector<P> ret;
	ret.emplace_back(P(0, 0));
	REP (i, ssize(t) - 1)
		ret.emplace_back(ret.back() + t[i]);
	return ret;
}
