/*
 * Opis: Wrapper na \texttt{std::complex}, pola \texttt{.x} oraz \texttt{.y} nie są const.
 *   Wiele operacji na \texttt{Point} zwraca complex, np \texttt{(p * p).x} się nie skompiluje.
 *   \texttt{P p = {5, 6}; abs(p) = length; arg(p) = kąt; polar(len, angle);}
 */
#pragma once
using D = long double;
struct P : complex<D> {
	D *m = (D *) this, &x, &y;
	P(D _x = 0, D _y = 0) : complex<D>(_x, _y), x(m[0]), y(m[1]) {}
	P(complex<D> c) : P(c.real(), c.imag()) {}
	P(const P &p) : P(p.x, p.y) {}
	P &operator=(const P &p) {
		x = p.x, y = p.y;
		return *this;
	}
};
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
