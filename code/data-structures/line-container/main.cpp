/*
 * Opis: O(\log n) set dla funkcji liniowych,
 *   \texttt{add(a, b)} dodaje funkcję $y = ax + b$
 *   \texttt{query(x)} zwraca największe $y$ w punkcie $x$.
 */

struct Line {
	mutable LL a, b, p;
	LL eval(LL x) const { return a * x + b; }
	bool operator<(const Line & o) const { return a < o.a; }
	bool operator<(LL x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// jak double to inf = 1 / .0, div(a, b) = a / b
	const LL inf = LLONG_MAX;
	LL div(LL a, LL b) { return a / b - ((a ^ b) < 0 && a % b); }
	bool intersect(iterator x, iterator y) {
		if(y == end()) { x->p = inf; return false; }
		if(x->a == y->a) x->p = x->b > y->b ? inf : -inf;
		else x->p = div(y->b - x->b, x->a - y->a);
		return x->p >= y->p;
	}
	void add(LL a, LL b) {
		auto z = insert({a, b, 0}), y = z++, x = y;
		while(intersect(y, z)) z = erase(z);
		if(x != begin() && intersect(--x, y))
			intersect(x, erase(y));
		while((y = x) != begin() && (--x)->p >= y->p)
			intersect(x, erase(y));
	}
	LL query(LL x) {
		assert(!empty());
		return lower_bound(x)->eval(x);
	}
};
