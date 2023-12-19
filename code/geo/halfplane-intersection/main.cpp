/*
 * Opis: O(n \log n) wyznaczanie punktów na brzegu/otoczce przecięcia podanych półpłaszczyzn.
 *   \texttt{Halfplane(a, b)} tworzy półpłaszczyznę wzdłuż prostej $a\to b$ z obszarem po lewej stronie wektora $a\to b$.
 *   Jeżeli zostało zwróconych mniej, niż trzy punkty, to pole przecięcia jest puste.
 *   Na przykład \texttt{halfplane\_intersection(\{Halfplane(P(2, 1), P(4, 2)), Halfplane(P(6, 3), P(2, 4)), Halfplane(P(-4, 7), P(4, 2))\}) == \{(4, 2), (6, 3), (0, 4.5)\}}.
 *   Pole przecięcia jest zawsze ograniczone, ponieważ w kodzie są dodawane cztery półpłaszczyzny o współrzędnych w \texttt{+/-inf}, ale nie należy na tym polegać przez eps oraz błędy precyzji (najlepiej jest zmniejszyć inf tyle, ile się da).
 */
#include "../point/main.cpp"
struct Halfplane {
	P p, pq;
	D angle;
	Halfplane() {}
	Halfplane(P a, P b) : p(a), pq(b - a) {
		angle = atan2l(pq.imag(), pq.real());
	}
};
ostream& operator<<(ostream&o, Halfplane h) {
	return o << '(' << h.p << ", " << h.pq << ", " << h.angle << ')';
}
bool is_outside(Halfplane hi, P p) {
	return sign(cross(hi.pq, p - hi.p)) == -1;
}
P inter(Halfplane s, Halfplane t) {
	D alpha = cross(t.p - s.p, t.pq) / cross(s.pq, t.pq);
	return s.p + s.pq * alpha;
}
vector<P> halfplane_intersection(vector<Halfplane> h) {
	for(int i = 0; i < 4; ++i) {
		constexpr D inf = 1e9;
		array box = {P(-inf, -inf), P(inf, -inf), P(inf, inf), P(-inf, inf)};
		h.emplace_back(box[i], box[(i + 1) % 4]);
	}
	sort(h.begin(), h.end(), [&](Halfplane l, Halfplane r) {
		return l.angle < r.angle;
	});
	deque<Halfplane> dq;
	for(auto &hi : h) {
		while(ssize(dq) >= 2 and is_outside(hi, inter(dq.end()[-1], dq.end()[-2])))
			dq.pop_back();
		while(ssize(dq) >= 2 and is_outside(hi, inter(dq[0], dq[1])))
			dq.pop_front();
		if(ssize(dq) and sign(cross(hi.pq, dq.back().pq)) == 0) {
			if(sign(dot(hi.pq, dq.back().pq)) < 0)
				return {};
			if(is_outside(hi, dq.back().p))
				dq.pop_back();
			else
				continue;
		}
		dq.emplace_back(hi);
	}
	while(ssize(dq) >= 3 and is_outside(dq[0], inter(dq.end()[-1], dq.end()[-2])))
		dq.pop_back();
	while(ssize(dq) >= 3 and is_outside(dq.end()[-1], inter(dq[0], dq[1])))
		dq.pop_front();
	vector<P> ret;
	REP(i, ssize(dq))
		ret.emplace_back(inter(dq[i], dq[(i + 1) % ssize(dq)]));
	ret.erase(unique(ret.begin(), ret.end(), [&](P l, P r) { return equal(l, r); }), ret.end());
	if(ssize(ret) >= 2 and equal(ret.front(), ret.back()))
		ret.pop_back();
	for(Halfplane hi : h)
		if(ssize(ret) <= 2 and is_outside(hi, ret[0]))
			return {};
	return ret;
}
