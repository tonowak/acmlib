/*
 * Opis: Przecięcie prostych lub odcinków
 * Użycie: intersection(a, b, c, d) zwraca przecięcie prostych ab oraz cd
 * v = intersect_segments(a, b, c, d, s) zwraca przecięcie odcinków ab oraz cd
 * if ssize(v) == 0: nie ma przecięć
 * if ssize(v) == 1: v[0] jest przecięciem
 * if ssize(v) == 2 in intersect_segments: (v[0], v[1]) to odcinek, w którym są wszystkie inf rozwiązań
 * if ssize(v) == 2 in intersect_lines: v to niezdefiniowane punkty (inf rozwiązań)
 */

#include "../point/main.cpp"

P intersection_lines(P a, P b, P c, P d) {
	D c1 = cross(c - a, b - a), c2 = cross(d - a, b - a);
	// zaklada, ze c1 != c2, tzn. proste nie sa rownolegle
	return (c1 * d  - c2 * c) / (c1 - c2);
}

bool on_segment(P a, P b, P p) {
	return equal(cross(a - p, b - p), 0) and dot(a - p, b - p) <= 0;
}

bool is_intersection_segment(P a, P b, P c, P d) {
	if(on_segment(a, b, c) or on_segment(a, b, d) or on_segment(c, d, a) or on_segment(c, d, b))
		return true;
	int acb = dir(a, c, b), adb = dir(a, d, b);
	int cad = dir(c, a, d), cbd = dir(c, b, d);
	if(acb != 0 and adb != 0 and acb == adb)
		return false;
	if(cad != 0 and cbd != 0 and cad == cbd)
		return false;
	if(acb == 0 and adb == 0)
		return false;
	return true;
}

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
}

vector<P> intersect_lines(P a, P b, P c, P d) {
	D acd = cross(c - a, d - c), bcd = cross(c - b, d - c);
	if(not equal(bcd, acd))
		return {(a * bcd - b * acd) / (bcd - acd)};
	return {a, a};
}
