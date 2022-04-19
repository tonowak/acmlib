#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto random_string = [](int n, int r) {
		string s(rd(1, n), 'a');
		for (auto& x : s)
			x = char('a' + rd(0, r - 1));
		return s;
	};

	auto to_vector = [](const string& x) {
		vector<int> v(ssize(x));
		REP(i,ssize(x))
			v[i] = int(x[i] - 'a');
		return v;
	};

	int r = rd(1, 26);
	auto s = random_string(30, r);
	int n = ssize(s);

	SuffixAutomaton sa;
	for (auto x : s)
		sa.add_letter(int(x - 'a'));

	set<string> ss;
	REP(i,n)
		FOR(j,1,n-i)
			ss.emplace(s.substr(i, j));

	for (auto x : ss) {
		auto v = to_vector(x);
		assert(sa.is_inside(v));
	}

	const int opcnt = 1e3;
	REP(ii,opcnt) {
		auto x = random_string(n + 1, r);
		auto v = to_vector(x);
		assert(sa.is_inside(v) == (ss.find(x) != ss.end()));
	}
}
