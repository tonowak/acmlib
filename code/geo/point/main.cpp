/*
 * Opis: Wrapper na \texttt{std::complex}, definy trzeba dać nad bitsami, wtedy istnieje \texttt{p.x()} oraz \texttt{p.y()}.
 *   \texttt{abs} długość, \texttt{arg} kąt $(-\pi, \pi]$ gdzie $(0,1)$ daje $\frac{\pi}{2}$, \texttt{polar(len, angle)} tworzy $P$. Istnieją \texttt{atan2}, \texttt{asin}, \texttt{sinh}.
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
namespace std { bool operator<(P a, P b) { return sign(a.x() - b.x()) == 0 ? sign(a.y() - b.y()) < 0 : a.x() < b.x(); } }
ostream& operator<<(ostream &o, P p) { return o << pair(p.x(), p.y()); }
// cross({1, 0}, {0, 1}) = 1
D cross(P a, P b) { return a.x() * b.y() - a.y() * b.x(); }
D dot(P a, P b) { return a.x() * b.x() + a.y() * b.y(); }
D dist(P a, P b) { return abs(a - b); }
int dir(P a, P b, P c) { return sign(cross(b - a, c - b)); }
