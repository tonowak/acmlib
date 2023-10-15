/*
 * Opis: O(n) po puszczeniu otoczki, zakłada n >= 2.
 */
#include "../convex-hull/main.cpp"

pair<P, P> furthest_pair(vector<P> in) {
	in = hull(in);
	int n = ssize(in), j = 1;
	pair<D, pair<P, P>> ret;
	REP(i, j)
		for(;; j = (j + 1) % n) {
			ret = max(ret, {dist(in[i], in[j]), {in[i], in[j]}});
			if (sign(cross(in[(j + 1) % n] - in[j], in[i + 1] - in[i])) <= 0)
				break;
		}
	return ret.second;
}
