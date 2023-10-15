/*
 * Opis: O(n log n), zakłada ssize(in) > 1.
 */
#include "../point/main.cpp"

pair<P, P> closest_pair(vector<P> in) {
	set<P> s;
	sort(in.begin(), in.end(), [](P a, P b) { return a.y < b.y; });
	pair<D, pair<P, P>> ret(1e18, {P(), P()});
	int j = 0;
	for (P p : in) {
		P d(1 + sqrt(ret.first), 0);
		while (in[j].y <= p.y - d.x) s.erase(in[j++]);
		auto lo = s.lower_bound(p - d), hi = s.upper_bound(p + d);
		for (; lo != hi; ++lo)
			ret = min(ret, {pow(dist(*lo, p), 2), {*lo, p}});
		s.insert(p);
	}
	return ret.second;
}
