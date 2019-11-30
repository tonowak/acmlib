/*
 * Opis: Przecięcie prostych lub odcinków
 * Użycie: v = intersect(a, b, c, d, s) zwraca przecięcie (s ? odcinków : prostych) ab oraz cd
 * if size(v) == 0: nie ma przecięć
 * if size(v) == 1: v[0] jest przecięciem
 * if size(v) == 2 and s: (v[0], v[1]) to odcinek, w którym są wszystkie inf rozwiązań
 * if size(v) == 2 and s == false: v to niezdefiniowane punkty (inf rozwiązań)
 */

#include "../point/main.cpp"

bool on_segment(P a, P b, P p) {
	return equal(cross(a - p, b - p), 0) and dot(a - p, b - p) <= 0;
}

vector<P> intersect(P a, P b, P c, P d, bool segments) {
	Double acd = cross(c - a, d - c), bcd = cross(c - b, d - c),
		   cab = cross(a - c, b - a), dab = cross(a - d, b - a);
	if((segments and sign(acd) * sign(bcd) < 0 and sign(cab) * sign(dab) < 0)
	   or (not segments and not equal(bcd, acd)))
		return {(a * bcd - b * acd) / (bcd - acd)};
	if(not segments)
		return {a, a};
	// skip for not segments
	set<P, Sortx> s;
	if(on_segment(c, d, a)) s.emplace(a);
	if(on_segment(c, d, b)) s.emplace(b);
	if(on_segment(a, b, c)) s.emplace(c);
	if(on_segment(a, b, d)) s.emplace(d);
	return {s.begin(), s.end()};
}


P intersect(P a, P b, P c, P d, bool segments) {
	Double c1 = cross(c - a, b - a), c2 = cross(d - a, b - a);
	if(c1 != c2) r
}
