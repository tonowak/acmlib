#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
#include "../convex-hull/main.cpp"

vector<P> brute_halfplane(vector<Halfplane> h) {
	vector<P> all_inter;
	for(Halfplane a : h)
		for(Halfplane b : h)
			if(not equal(cross(a.pq, b.pq), 0))
				all_inter.emplace_back(inter(a, b));
	debug(all_inter);
	vector<P> potential;
	for(P p : all_inter) {
		bool is_good = true;
		for(Halfplane hi : h)
			if(is_outside(hi, p)) {
				is_good = false;
				break;
			}
		if(is_good)
			potential.emplace_back(p);
	}
	debug(potential);

	vector<P> got_hull = hull(potential);
	debug(got_hull);
	return got_hull;
}

void test() {
	const int n = rd(0, 10);
	vector<Halfplane> in;
	for(int i = 0; i < 4; ++i) {
		constexpr D inf = 1e5;
		array box = {P(-inf, -inf), P(inf, -inf), P(inf, inf), P(-inf, inf)};
		in.emplace_back(box[i], box[(i + 1) % 4]);
	}
	const int lg = rd(0, 30);
	const int mx = 1 << lg;
	auto get_random_p = [&] {
		return P(rd(-mx, mx), rd(-mx, mx));
	};
	REP(i, n) {
		P a, b;
		while(true) {
			a = get_random_p();
			b = get_random_p();
			if(a != b)
				break;
		}
		in.emplace_back(a, b);
	}
	debug(in);
	auto ans_main = halfplane_intersection(in);
	auto ans_brute = brute_halfplane(in);
	debug(ans_main, ans_brute);
	sort(ans_main.begin(), ans_main.end());
	sort(ans_brute.begin(), ans_brute.end());
	ans_brute.erase(unique(ans_brute.begin(), ans_brute.end(), [&](P l, P r) { return equal(l, r); }), ans_brute.end());
	assert(ssize(ans_main) == ssize(ans_brute));
	REP(i, ssize(ans_main))
		assert(equal(ans_main[i], ans_brute[i]));
}
