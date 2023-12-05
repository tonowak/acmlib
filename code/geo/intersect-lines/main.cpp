/*
 * Opis: O(1) ale intersect\_segments ma sporą stałą (ale działa na wszystkich edge-case'ach).
 *   Jeżeli intersect\_segments zwróci dwa punkty to wszystkie $\inf$ rozwiązań są pomiędzy.
 */
#include "../point/main.cpp"
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
