#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 30);
	int r = rd(1, 26);
	string s(n, 'a');
	for (auto& x : s)
		x = char('a' + rd(0, r - 1));

	SuffixArray sa(s);

	vector<pair<string,int>> v(n + 1);
	REP(i,n+1)
		v[i] = {s.substr(i, n - i), i};
	sort(v.begin(), v.end());

	REP(i,n+1)
		assert(sa.sa[i] == v[i].second);

	auto common = [&](const string& a, const string& b) {
		int d = min(ssize(a), ssize(b));
		REP(i,d)
			if (a[i] != b[i])
				return i;
		return d;
	};
	REP(i,n)
		assert(sa.lcp[i + 1] == common(v[i].first, v[i + 1].first));
}
