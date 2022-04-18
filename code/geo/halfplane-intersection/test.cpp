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
	int n = rd(0, 10);
	vector<Halfplane> in;
	for(int i = 0; i < 4; ++i) {
		constexpr D inf = 1e5;
		array box = {P(-inf, -inf), P(inf, -inf), P(inf, inf), P(-inf, inf)};
		in.emplace_back(box[i], box[(i + 1) % 4]);
	}
	constexpr int mx = 20;
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
	auto ans1 = halfplane_intersection(in);
	auto ans2 = brute_halfplane(in);
	debug(ans1, ans2);
	sort(ans1.begin(), ans1.end());
	sort(ans2.begin(), ans2.end());
	ans2.erase(unique(ans2.begin(), ans2.end()), ans2.end());
	assert(ssize(ans1) == ssize(ans2));
	REP(i, ssize(ans1))
		assert(ans1[i] == ans2[i]);
}
