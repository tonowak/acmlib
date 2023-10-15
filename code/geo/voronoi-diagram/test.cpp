#include <bits/stdc++.h>
using namespace std;
ostream& operator<<(ostream &o, __int128_t x) {
	string s;
	if(x == 0)
		s = "0";
	else
		while(x > 0) {
			s += char('0' + (x % 10));
			x /= 10;
		}
	reverse(s.begin(), s.end());
	return o << s.data();
}

#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
#include "../intersect-lines/main.cpp"

D rd_d(int l, int r) {
	return uniform_real_distribution<D>(l, r)(tester_rng);
}

void test() {
	int mx = rd(0, 100) > 0 ? 5 : int(3e8);
	int n = mx > 5 ? rd(1, int(1e3)) : rd(1, 10);
	set<PI> already;
	vector<PI> in(n);
	for(auto &[x, y] : in) {
		while(true) {
			x = rd(-mx, mx);
			y = rd(-mx, mx);
			if(already.find(pair(x, y)) == already.end())
				break;
		}
		already.emplace(x, y);
	}
	debug(in);
	auto ret = voronoi_faces(in, mx);
	debug(ret);

	assert(ssize(ret) == n);
	for(auto poly : ret) {
		assert(ssize(poly) >= 3);
		REP(i, ssize(poly)) {
			P p0 = poly[i];
			P p1 = poly[(i + 1) % ssize(poly)];
			P p2 = poly[(i + 2) % ssize(poly)];
			assert(dir(p0, p1, p2) < 0);
		}
	}

	int queries = 10;
	while(queries --> 0) {
		D x, y;
		if(rd(0, 1)) {
			x = rd_d(-mx, mx);
			y = rd_d(-mx, mx);
		}
		else {
			x = rd(mx, mx);
			y = rd(mx, mx);
		}
		debug(x, y);

		vector<int> matching_areas;
		REP(id, ssize(ret)) {
			auto poly = ret[id];
			int inter_cnt = 0;
			REP(i, ssize(poly))
				if(on_segment(poly[i], poly[(i + 1) % ssize(poly)], P(x, y)))
					++inter_cnt;
			if(inter_cnt > 0) {
				matching_areas.emplace_back(id);
				continue;
			}
				
			REP(i, ssize(poly))
				if(is_intersection_segment(P(x, y), P(int(2e9), y + 1), poly[i], poly[(i + 1) % ssize(poly)]))
					++inter_cnt;
			assert(inter_cnt <= 2);
			if(inter_cnt == 1)
				matching_areas.emplace_back(id);
		}
		debug(ssize(matching_areas));
		debug(matching_areas);

		D closest_d = 3e9;
		REP(i, n)
			closest_d = min(closest_d, dist(P(x, y), P(in[i].first, in[i].second)));
		vector<int> closest_v;
		REP(i, n)
			if(equal(closest_d, dist(P(x, y), P(in[i].first, in[i].second))))
				closest_v.emplace_back(i);
		debug(closest_v);
		sort(matching_areas.begin(), matching_areas.end());
		sort(closest_v.begin(), closest_v.end());
		assert(matching_areas == closest_v);
	}
}
