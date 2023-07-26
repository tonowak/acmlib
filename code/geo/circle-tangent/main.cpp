/*
 * Opis: O(1), dla punktu $p$ oraz okręgu o promieniu $r$ i środku $o$ zwraca punkty $p_0, p_1$ będące punktami styczności prostych stycznych do okręgu. Zakłada, że $abs(p) > r$.
 */
#include "../point/main.cpp"
pair<P, P> tangents_to_circle(P o, D r, P p) {
	p -= o;
	D r2 = r * r;
	D d2 = dot(p, p);
	assert(sign(d2 - r2) > 0);
	P ret0 = (r2 / d2) * p;
	P ret1 = r / d2 * sqrt(d2 - r2) * P(-p.y, p.x);
	return {o + ret0 + ret1, o + ret0 - ret1};
}
