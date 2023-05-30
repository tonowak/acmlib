#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 30);
	int r = rd(1, 26);
	vector<int> s(n);
	for (auto& x : s)
		x = rd(0, r - 1);

	vector<int> sa = suffix_array(s, r);
	vector<int> lcp = get_lcp(s, sa);

	vector<pair<vector<int>,int>> v(n + 1);
	REP(i,n+1)
		v[i] = {vector(s.begin() + i, s.end()), i};
	sort(v.begin(), v.end());

	REP(i,n+1)
		assert(sa[i] == v[i].second);

	auto common = [&](const vector<int>& a, const vector<int>& b) {
		int d = min(ssize(a), ssize(b));
		REP(i,d)
			if (a[i] != b[i])
				return i;
		return d;
	};
	REP(i,n)
		assert(lcp[i] == common(v[i].first, v[i + 1].first));
}
