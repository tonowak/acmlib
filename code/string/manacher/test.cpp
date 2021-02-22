#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 10);
	vector<int> in(n);
	for(int &x : in)
		x = rd(0, 1);

	array<vector<int>, 2> radius = {vector<int>(n - 1), vector<int>(n)};
	REP(l, n)
		FOR(r, l, n - 1) {
			vector<int> s;
			FOR(i, l, r)
				s.emplace_back(in[i]);
			vector<int> cp = s;
			reverse(cp.begin(), cp.end());
			if(cp != s)
				continue;

			int mid = (l + r) / 2, len = r - l + 1;
			radius[len % 2][mid] = max(radius[len % 2][mid], len / 2);
		}
	assert(radius == manacher(in));
}
