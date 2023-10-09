#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool check_equiv(vector<P> a, vector<P> b) {
	if (ssize(a) != ssize(b))
		return false;
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	REP (i, ssize(a))
		if (!equal(a[i], b[i]))
			return false;
	return true;
}

void test() {
	int points_type = rd(0, 1);
	auto rd_D = [&] {
		if(points_type)
			return D(rd(-5, 5));
		else
			return D(rd(-1e9, 1e9)) / 1e6;
	};
	int n = rd(0, 1) ? rd(0, 10) : rd(0, 1000);
	vector<P> t(n);
	REP (i, n)
		while (true) {
			t[i] = P(rd_D(), rd_D());
			if(t[i] != P(0, 0))
				break;
		}
	debug(t);
	auto sorted_t = angle_sort(t);
	debug(sorted_t);
	assert(check_equiv(t, sorted_t));
	REP (i, n - 1)
		assert((sorted_t[i + 1] < P(0, 0)) >= (sorted_t[i] < P(0, 0)));
	REP (i, n - 1)
		if ((sorted_t[i] < P(0, 0)) == (sorted_t[i + 1] < P(0, 0)))
			assert(cross(sorted_t[i], sorted_t[i + 1]) < eps);
}
