/*
 * Opis: Wrapper na \texttt{std::complex}, pola \texttt{.x} oraz \texttt{.y} nie są const.
 *   Wiele operacji na \texttt{Point} zwraca complex, np \texttt{(p * p).x} się nie skompiluje.
 *   \texttt{P p = {5, 6}; abs(p) = length; arg(p) = kąt; polar(len, angle);}
 */
#pragma once
template <class T>
struct Point : complex<T> {
	T *m = (T *) this, &x, &y;
	Point(T _x = 0, T _y = 0) : complex<T>(_x, _y), x(m[0]), y(m[1]) {}
	Point(complex<T> c) : Point(c.real(), c.imag()) {}
	Point(const Point &p) : Point(p.x, p.y) {}
	Point &operator=(const Point &p) {
		x = p.x, y = p.y;
		return *this;
	}
};
using D = long double;
using P = Point<D>;
constexpr D eps = 1e-9;
istream &operator>>(istream &is, P &p) { return is >> p.x >> p.y; }
bool equal(D a, D b) { return abs(a - b) < eps; }
bool equal(P a, P b) { return equal(a.x, b.x) and equal(a.y, b.y); }
int sign(D a) { return equal(a, 0) ? 0 : a > 0 ? 1 : -1; }
bool operator<(P a, P b) { return tie(a.x, a.y) < tie(b.x, b.y); }
// cross({1, 0}, {0, 1}) = 1
D cross(P a, P b) { return a.x * b.y - a.y * b.x; }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
D dist(P a, P b) { return abs(a - b); }
int dir(P a, P b, P c) { return sign(cross(b - a, c - b)); }
