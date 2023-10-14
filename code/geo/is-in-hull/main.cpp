/*
 * Opis: O(\log n), zwraca czy punkt jest wewnątrz otoczki h.
 * Zakłada że punkty są clockwise, różne oraz nie ma trzech współliniowych (działa na convex-hull).
 */
#include "../intersect-lines/main.cpp"

bool is_in_hull(vector<P> h, P p, bool can_on_edge) {
	if(ssize(h) < 3) return can_on_edge and on_segment(h[0], h.back(), p);
	int l = 1, r = ssize(h) - 1;
	if(dir(h[0], h[l], p) >= can_on_edge or dir(h[0], h[r], p) <= -can_on_edge)
		return false;
	while(r - l > 1) {
		int m = (l + r) / 2;
		(dir(h[0], h[m], p) < 0 ? l : r) = m;
	}
	return dir(h[l], h[r], p) < can_on_edge;
}
