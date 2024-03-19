#define real x
#define imag y
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r)for(int i=(l);i<=(r);++i)
#define REP(i,n)FOR(i,0,(n)-1)
#define ssize(x)int(x.size())
#ifdef DEBUG
auto&operator<<(auto&o,pair<auto,auto>p){return o<<"("<<p.first<<", "<<p.second<<")";}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<"{";int i=0;for(auto e:x)o<<","+!i++<<e;return o<<"}";}
#define debug(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X)
#else
#define debug(...){}
#endif

/*
 * Opis: Generatorka wielokątów niekoniecznie-wypukłych.
 * Zwraca wielokąt z co najmniej $n \cdot \texttt{PROC}$ punktami w zakresie $[-\texttt{range}, \texttt{range}]$.
 * Jeśli $n$ $(n > 2)$ jest około $\texttt{range}^{\frac{2}{3}}$, to powinno chodzić O(n \log n).
 * Dla większych $n$ może nie dać rady.
 * Ostatni punkt jest zawsze w $(0, 0)$ - można dodać przesunięcie o wektor dla pełnej losowości.
 */

/*
 * Opis: Wrapper na \texttt{std::complex}, definy trzeba dać nad bitsami, wtedy istnieje \texttt{p.x()} oraz \texttt{p.y()}.
 *   \texttt{abs} długość, \texttt{arg} kąt $(-\pi, \pi]$ gdzie $(0,1)$ daje $\frac{\pi}{2}$, \texttt{polar(len, angle)} tworzy $P$. Istnieją \texttt{atan2}, \texttt{asin}, \texttt{sinh}.
 */
using D = long double;
using P = complex<D>;
constexpr D eps = 1e-9;
bool equal(D a, D b) { return abs(a - b) < eps; }
bool equal(P a, P b) { return equal(a.x(), b.x()) and equal(a.y(), b.y()); }
int sign(D a) { return equal(a, 0) ? 0 : a > 0 ? 1 : -1; }
namespace std { bool operator<(P a, P b) { return sign(a.x() - b.x()) == 0 ? sign(a.y() - b.y()) < 0 : a.x() < b.x(); } }
// cross({1, 0}, {0, 1}) = 1
D cross(P a, P b) { return a.x() * b.y() - a.y() * b.x(); }
D dot(P a, P b) { return a.x() * b.x() + a.y() * b.y(); }
D dist(P a, P b) { return abs(a - b); }
int dir(P a, P b, P c) { return sign(cross(b - a, c - b)); }

/*
 * Opis: O(1) ale intersect\_segments ma sporą stałą (ale działa na wszystkich edge-case'ach).
 *   Jeżeli intersect\_segments zwróci dwa punkty to wszystkie $\inf$ rozwiązań są pomiędzy.
 */
// BEGIN HASH
P intersect_lines(P a, P b, P c, P d) {
    D c1 = cross(c - a, b - a), c2 = cross(d - a, b - a);
    // c1 == c2 => równoległe
    return (c1 * d  - c2 * c) / (c1 - c2);
} // END HASH
// BEGIN HASH
bool on_segment(P a, P b, P p) {
    return equal(cross(a - p, b - p), 0) and sign(dot(a - p, b - p)) <= 0;
} // END HASH
// BEGIN HASH
bool is_intersection_segment(P a, P b, P c, P d) {
    auto aux = [&](D q, D w, D e, D r) {
        return sign(max(q, w) - min(e, r)) >= 0;
    };
    return  aux(c.x(), d.x(), a.x(), b.x()) and aux(a.x(), b.x(), c.x(), d.x())
        and aux(c.y(), d.y(), a.y(), b.y()) and aux(a.y(), b.y(), c.y(), d.y())
        and dir(a, d, c) * dir(b, d, c) != 1
        and dir(d, b, a) * dir(c, b, a) != 1;
} // END HASH
// BEGIN HASH
vector<P> intersect_segments(P a, P b, P c, P d) {
    D acd = cross(c - a, d - c), bcd = cross(c - b, d - c),
           cab = cross(a - c, b - a), dab = cross(a - d, b - a);
    if(sign(acd) * sign(bcd) < 0 and sign(cab) * sign(dab) < 0)
        return {(a * bcd - b * acd) / (bcd - acd)};
    set<P> s;
    if(on_segment(c, d, a)) s.emplace(a);
    if(on_segment(c, d, b)) s.emplace(b);
    if(on_segment(a, b, c)) s.emplace(c);
    if(on_segment(a, b, d)) s.emplace(d);
    return {s.begin(), s.end()};
} // END HASH

/*
 * Opis: Dodatek do generatorki
 */
mt19937 rng(random_device{}());
int rd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}
vector<P> gen_polygon(int n, int range) {
    assert(n > 2);
    vector<P> t;
    while (ssize(t) < n) {
        P p(rd(-range, range), rd(-range, range));
        if (find(t.begin(), t.end(), p) == t.end()) {
            bool ok = true;
            REP (i, ssize(t))
                REP (j, i)
                    if (dir(t[i], t[j], p) == 0)
                        ok = false;
            if (ok)
                t.emplace_back(p);
            debug(ssize(t), t);
        }
    }
    while ([&]() {
        debug(t);
        bool ret = false;
        REP (i, n)
            REP (j, i - 1)
                if ((i + 1) % n != j && ssize(intersect_segments(t[i], t[(i + 1) % n], t[j], t[j + 1]))) {
                    swap(t[(i + rd(0, 1)) % n], t[(j + rd(0, 1)) % n]);
                    ret = true;
                }
        return ret;
    }()) {}
    return t;
}

void printPolygonSVG(vector<P> v, int r) {
    int m = 350 / r;
    int d = 50;
    auto ori = v;
    for (auto &p : v)
        p = P((p.x() + r * 1.1) * m, (p.y() + r * 1.1) * m);
    r = int(r * m * 2.5);
    printf("<svg height='%d' width='%d'>", r, r);
    printf("<rect width='100%%' height='100%%' fill='white' />");
    int n = ssize(v);
    REP (i, n) {
        printf("<line x1='%Lf' y1='%Lf' x2='%Lf' y2='%Lf' style='stroke:black' />", v[i].x(), v[i].y(), v[(i + 1) % n].x(), v[(i + 1) % n].y());
        printf("<circle cx='%Lf' cy='%Lf' r='%f' fill='red' />", v[i].x(), v[i].y(), r / d / 10.0);
        printf("<text x='%Lf' y='%Lf' font-size='%d' fill='violet'>%d (%.1Lf, %.1Lf)</text>", v[i].x() + 5, v[i].y() - 5, r / d, i + 1, ori[i].x(), ori[i].y());
    }
    printf("</svg>");
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    auto v = gen_polygon(8, 10);
    debug(v);
    printPolygonSVG(v, 10);
}
