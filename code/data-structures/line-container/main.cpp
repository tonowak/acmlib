/*
 * Status: Przetestowane
 * Opis: Set dla funkcji liniowych
 * Czas: O(\log n)
 */

struct Line {
	mutable LL a, b, p;
	LL eval(LL x) { return a * x + b; }
	bool operator<(const Line & o) const { return a < o.a; }
	bool operator<(LL x) const { return p < x; }
};

constexpr LL inf = 1e18 + 7;
LL divide(LL a, LL b) { return a / b - ((a ^ b) < 0 && a % b); }
LL better(const Line &x, const Line &y) {
	if(x.a == y.a) return x.b >= y.b ? inf : -inf;
	return divide(y.b - x.b, x.a - y.a);
}

struct LineContainer : multiset<Line, less<>> {
	bool intersect(iterator x, iterator y) {
		if(y == end()) { x->p = inf; return 0; }
		x->p = better(*x, *y);
		return x->p >= y->p;
	}
	void add(LL a, LL b) {
		auto z = insert({a, b, 0}), y = z++, x = y;
		while(intersect(y, z)) z = erase(z);
		if(x != begin() && intersect(--x, y)) intersect(x, y = erase(y));
		while((y = x) != begin() && (--x)->p >= y->p)
			intersect(x, erase(y));
	}
	LL query(LL x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.eval(x);
	}
};
