#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	vector<int> s;
	REP(i, n)
		s.emplace_back(vector{0, 13, 25}[rd(0, 2)]);
	Hashing hashing(s, 31);
	auto get_interval = [&](int l, int r) {
		if(l > r)
			swap(l, r);
		return pair(hashing(l, r), vector(s.begin() + l, s.begin() + r + 1));
	};
	auto [h0, s0] = get_interval(rd(0, n - 1), rd(0, n - 1));
	auto [h1, s1] = get_interval(rd(0, n - 1), rd(0, n - 1));
	assert(bool(h0 == h1) == bool(s0 == s1));
}
