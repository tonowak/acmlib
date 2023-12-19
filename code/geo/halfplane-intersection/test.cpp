#include "../point/before_bits.cpp"
#include <bits/stdc++.h>
using namespace std;
ostream& operator<<(ostream &o, __int128 x) {
	return o << (long long)(x);
}
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
#include "../convex-hull/main.cpp"
#include "../../math/bignum/main.cpp"

using Frac = pair<Num, Num>;
using PInt = pair<int, int>;
using PFrac = pair<Frac, Frac>;
using HalfplanePInt = pair<PInt, PInt>; // (punkt p, vector pq)

LL crossPInt(PInt l, PInt r) {
	return l.first * LL(r.second) - l.second * LL(r.first);
}

Frac to_frac(int x) {
	return {x, 1};
}
PFrac to_pfrac(PInt p) {
	return {to_frac(p.first), to_frac(p.second)};
}
Frac mul(int x, Frac y) {
	return {y.first * x, y.second};
}
Frac add(Frac l, Frac r) {
	return {l.first * r.second + l.second * r.first, l.second * r.second};
}
PFrac add_pfrac(PFrac l, PFrac r) {
	return {add(l.first, r.first), add(l.second, r.second)};
}
Frac neg(Frac x) {
	return {-x.first, x.second};
}
PFrac sub_pfrac(PFrac l, PFrac r) {
	return {add(l.first, neg(r.first)), add(l.second, neg(r.second))};
}
Frac mul_frac(Frac l, Frac r) {
	return {l.first * r.first, l.second * r.second};
}
PFrac mul_pfrac(PFrac l, Frac r) {
	return {mul_frac(l.first, r), mul_frac(l.second, r)};
}
Frac crossPFrac(PFrac l, PFrac r) {
	return add(mul_frac(l.first, r.second), neg(mul_frac(l.second, r.first)));
}

bool is_outside(HalfplanePInt hi, PFrac p) {
	// return cross(hi.second, p - hi.first) < 0;
	PFrac l = to_pfrac(hi.second);
	PFrac r = sub_pfrac(p, to_pfrac(hi.first));
	Frac prod = crossPFrac(l, r);
	return prod.first.sign * prod.second.sign < 0;
}

D num_to_d(Num n) {
	D d = 0;
	for(int x : vector(n.x.rbegin(), n.x.rend()))
		d = n.base * d + x;
	d *= n.sign;
	return d;
}
D to_d(Frac f) {
	return num_to_d(f.first) / num_to_d(f.second);
}
P to_p(PFrac f) {
	return {to_d(f.first), to_d(f.second)};
}

PInt sub_PInt(PInt l, PInt r) {
	return {l.first - r.first, l.second - r.second};
}

vector<P> brute_halfplane(vector<HalfplanePInt> h) {
	vector<P> potential;
	for(HalfplanePInt s : h)
		for(HalfplanePInt t : h)
			if(crossPInt(s.second, t.second) != 0) {
				Frac alpha = {crossPInt(sub_PInt(t.first, s.first), t.second),
					crossPInt(s.second, t.second)
				};
				PFrac inte = add_pfrac(to_pfrac(s.first), mul_pfrac(to_pfrac(s.second), alpha));

				bool is_good = true;
				for(HalfplanePInt hi : h)
					if(is_outside(hi, inte)) {
						is_good = false;
						break;
					}
				if(is_good)
					potential.emplace_back(to_p(inte));
			}

	vector<P> got_hull = hull(potential);
	return got_hull;
}

void test() {
	const int n = rd(0, 10);
	vector<Halfplane> in;
	vector<HalfplanePInt> inPInt;
	for(int i = 0; i < 4; ++i) {
		constexpr D inf = 1e5;
		array box = {P(-inf, -inf), P(inf, -inf), P(inf, inf), P(-inf, inf)};
		array boxPInt = {PInt(-inf, -inf), PInt(inf, -inf), PInt(inf, inf), PInt(-inf, inf)};
		in.emplace_back(box[i], box[(i + 1) % 4]);
		inPInt.emplace_back(boxPInt[i], sub_PInt(boxPInt[(i + 1) % 4], boxPInt[i]));
	}
	const int lg = rd(0, 30);
	const int mx = 1 << lg;
	auto get_random_p = [&] {
		return PInt(rd(-mx, mx), rd(-mx, mx));
	};
	REP(i, n) {
		PInt a, b;
		while(true) {
			a = get_random_p();
			b = get_random_p();
			if(a != b)
				break;
		}
		in.emplace_back(P(a.first, a.second), P(b.first, b.second));
		inPInt.emplace_back(a, sub_PInt(b, a));
	}
	debug(in);
	auto ans_main = halfplane_intersection(in);
	auto ans_brute = brute_halfplane(inPInt);
	debug(ans_main, ans_brute);
	sort(ans_main.begin(), ans_main.end());
	sort(ans_brute.begin(), ans_brute.end());
	ans_brute.erase(unique(ans_brute.begin(), ans_brute.end(), [&](P l, P r) { return equal(l, r); }), ans_brute.end());
	assert(ssize(ans_main) == ssize(ans_brute));
	REP(i, ssize(ans_main))
		assert(equal(ans_main[i], ans_brute[i]));
}
