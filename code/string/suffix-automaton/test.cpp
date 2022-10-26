#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto random_vec = [](int n, int r) {
		vector<int> s(rd(1, n));
		for (auto& x : s)
			x = rd(0, r - 1);
		return s;
	};

	int r = rd(1, 26);
	auto s = random_vec(30, r);
	int n = ssize(s);

	SuffixAutomaton sa;
	for (auto x : s)
		sa.add_letter(x);

	set<vector<int>> ss;
	REP(i,n)
		FOR(j,1,n-i)
			ss.emplace(vector(s.begin() + i, s.begin() + i + j));

	for (auto x : ss)
		assert(sa.is_inside(x));

	const int opcnt = 1e3;
	REP(ii,opcnt) {
		auto x = random_vec(n + 1, r);
		assert(sa.is_inside(x) == (ss.find(x) != ss.end()));
	}
}
