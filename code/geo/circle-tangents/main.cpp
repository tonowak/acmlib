/*
 * Opis: O(1), dla dwóch okręgów zwraca dwie styczne (wewnętrzne lub zewnętrzne, zależnie od wartości inner).
 * Zwraca \texttt{1 + sign(dist(p0, p1) - (inside ? r0 + r1 : abs(r0 - r1)))} rozwiązań, albo $0$ gdy $p1=p2$.
 * Działa gdy jakiś promień jest 0 -- przydatne do policzenia stycznej punktu do okręgu.
 */
#include "../point/main.cpp"
vector<pair<P, P>> circle_tangents(P p1, D r1, P p2, D r2, bool inner) {
	if(inner) r2 *= -1;
	P d = p2 - p1;
	D dr = r1 - r2, d2 = dot(d, d), h2 = d2 - dr * dr;
	if(equal(d2, 0) or sign(h2) < 0)
		return {};
	vector<pair<P, P>> ret;
	for(D sign : {-1, 1}) {
		P v = (d * dr + P(-d.y(), d.x()) * sqrt(max(D(0), h2)) * sign) / d2;
		ret.emplace_back(p1 + v * r1, p2 + v * r2);
	}
	ret.resize(1 + (sign(h2) > 0));
	return ret;
}
