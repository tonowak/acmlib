#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(0, 20);
	int mx = rd(0, 1) ? 10 : int(1e9);

	vector<pair<int, int>> in(n);
	for(auto &[x, y] : in) {
		x = rd(-mx, mx);
		y = rd(-mx, mx);
	}

	bool all_unique = true;
	REP(i, n)
		REP(j, i)
			if(in[i] == in[j])
				all_unique = false;
	if(not all_unique)
		return;

	auto ret = triangulate(in);

	bool is_all_colinear = true;
	if(n >= 2)
		REP(i, n)
			if(cross(in[0], in[1], in[i]) != 0)
				is_all_colinear = false;

	if(is_all_colinear) {
		assert(ret.empty());
		return;
	}
	assert(not ret.empty());
	assert(ssize(ret) % 3 == 0);

	array<vector<pair<int, int>>, 2> hulls;
	sort(in.begin(), in.end());
	REP(dir, 2) {
		auto &hull = hulls[dir];
		for(auto p : in) {
			while(ssize(hull) >= 2 and cross(hull.end()[-2], hull.back(), p) >= 0)
				hull.pop_back();
			hull.emplace_back(p);
		}
		reverse(in.begin(), in.end());
		hull.pop_back();
	}
	hulls[0].insert(hulls[0].end(), hulls[1].begin(), hulls[1].end());
	auto &hull = hulls[0];

	LL correct_area = 0;
	REP(i, ssize(hull))
		correct_area += hull[i] * hull[(i + 1) % ssize(hull)];

	LL triangles_area = 0;
	REP(i, ssize(ret) / 3)
		triangles_area += cross(ret[3 * i], ret[3 * i + 1], ret[3 * i + 2]);

	triangles_area *= -1;

	assert(correct_area == triangles_area);

	assert(H == nullptr);
}
