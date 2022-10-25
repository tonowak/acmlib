/*
 * Opis: Wyznacza górną otoczkę wypukłą online.
 * Czas: O(log n) na każdą operację dodania
 */

using P = pair<int, int>;
LL operator*(P l, P r) {
	return l.first * LL(r.second) - l.second * r.first;
}
P operator-(P l, P r) {
	return {l.first - r.first, l.second - r.second};
}
int sign(LL x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}
int dir(P a, P b, P c) {
	return sign((b - a) * (c - b));
}

struct UpperConvexHull {
	set<P> hull;

	void add_point(P p) {
		if(hull.empty()) {
			hull = {p};
			return;
		}
		auto it = hull.lower_bound(p);
		if(*hull.begin() < p and p < *prev(hull.end())) {
			assert(it != hull.end() and it != hull.begin());
			if(dir(*prev(it), p, *it) >= 0)
				return;
		}
		it = hull.emplace(p).first;
		auto have_to_rm = [&](auto iter) {
			if(iter == hull.end() or next(iter) == hull.end() or iter == hull.begin())
				return false;
			return dir(*prev(iter), *iter, *next(iter)) >= 0;
		};
		while(have_to_rm(next(it)))
			it = prev(hull.erase(next(it)));
		while(it != hull.begin() and have_to_rm(prev(it)))
			it = hull.erase(prev(it));
	}
};
