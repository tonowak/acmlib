/*
 * Opis: konwersja różnych postaci prostej
 */

#include "../point/main.cpp"
struct Line {
	using D = Double;
	D A, B, C;
	// postac ogolna Ax + By + C = 0
	Line(D A, D B, D C) : A(A), B(B), C(C) {}
	tuple<D, D, D> get_sta() { return {A, B, C}; }
	// postac kierunkowa ax + b = y
	Line(D a, D b) : A(a), B(-1), C(b) {}
	pair<D, D> get_dir() { return {- A / B, - C / B}; }
	// prosta pq
	Line(P p, P q) {
		assert(not equal(p.x, q.x) or not equal(p.y, q.y));
		if(!equal(p.x, q.x)) {
			A = (q.y - p.y) / (p.x - q.x);
			B = 1, C = -(A * p.x + B * p.y);
		}
		else A = 1, B = 0, C = -p.x;
	}
	pair<P, P> get_pts() { 
		if(!equal(B, 0)) return { P(0, - C / B), P(1, - (A + C) / B) };
		return { P(- C / A, 0), P(- C / A, 1) };
	}
};
