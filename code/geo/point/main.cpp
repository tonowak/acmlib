/*
 * Opis: Wrapper na \texttt{std::complex}, pola \texttt{.x} oraz \texttt{.y} nie są const.
 *   Wiele operacji na \texttt{Point} zwraca complex, np \texttt{(p * p).x} się nie skompiluje.
 *   \texttt{P p = {5, 6}; abs(p) = length; arg(p) = kąt; polar(len, angle);}
 */
#pragma once
// Before include bits:
// #define real x
// #define imag y
using D = long double;
using P = complex<D>;
constexpr D eps = 1e-9;
bool equal(D a, D b) { return abs(a - b) < eps; }
bool equal(P a, P b) { return equal(a.x(), b.x()) and equal(a.y(), b.y()); }
int sign(D a) { return equal(a, 0) ? 0 : a > 0 ? 1 : -1; }
bool operator<(P a, P b) { return pair(a.x(), a.y()) < pair(b.x(), b.y()); }
ostream& operator<<(ostream &o, P p) { return o << pair(p.x(), p.y()); }
// cross({1, 0}, {0, 1}) = 1
D cross(P a, P b) { return a.x() * b.y() - a.y() * b.x(); }
D dot(P a, P b) { return a.x() * b.x() + a.y() * b.y(); }
D dist(P a, P b) { return abs(a - b); }
int dir(P a, P b, P c) { return sign(cross(b - a, c - b)); }
