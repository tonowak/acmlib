/*
 * Opis: Wrapper na std::complex, pola .x oraz .y nie są const
 * wiele operacji na Point zwraca complex, np (p * p).x się nie skompiluje
 * Użycie: P p = {5, 6}; abs(p) = length; arg(p) = kąt; polar(len, angle);
 * exp(angle)
 */
#pragma once

template <class T>
struct Point : complex<T> {
    T *m = (T *) this, &x, &y;
    Point(T _x = 0, T _y = 0) : complex<T>(_x, _y), x(m[0]), y(m[1]) {}
    Point(complex<T> c) : complex<T>(c), x(m[0]), y(m[1]) {}
    Point(const Point &p) : complex<T>(p.x, p.y), x(m[0]), y(m[1]) {}
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
int sign(D a) { return equal(a, 0) ? 0 : a > 0 ? 1 : -1; }
bool operator<(P a, P b) { return tie(a.x, a.y) < tie(b.x, b.y); }

// cross({1, 0}, {0, 1}) = 1
D cross(P a, P b) { return a.x * b.y - a.y * b.x; }
D dot(P a, P b) { return a.x * b.x + a.y * b.y; }
D dist(P a, P b) { return abs(a - b); }
