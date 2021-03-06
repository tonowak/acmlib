#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	ordered_set<int> s;
	int n = rd(1, 100);
	vector<int> a(n);
	REP(i, n) {
		while(a[i] == 0 || s.find(a[i]) != s.end())
			a[i] = rd(1, 1000000000);
		s.insert(a[i]);
	}

	sort(a.begin(), a.end());
	REP(i, n)
		assert(a[i] == *s.find_by_order(i));
}
