#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<P> top_hull(vector<P> pts) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<P> top;
	for(auto p : pts) {
		while(ssize(top) > 1 and dir(top.end()[-2], top.back(), p) >= 0)
			top.pop_back();
		top.emplace_back(p);
	}
	return top;
}

void test() {
	int n = rd(1, 10);
	const int mx = vector<int>{10, int(1e5), int(1e9)}[rd(0, 2)];
	UpperConvexHull online;
	vector<P> curr;
	while(n --> 0) {
		P p = {rd(-mx, mx), rd(-mx, mx)};
		curr.emplace_back(p);
		online.add_point(p);
		auto brute = top_hull(curr);
		auto main = vector<P>(online.hull.begin(), online.hull.end());
		debug(curr, brute, main);
		assert(brute == main);
	}
}
