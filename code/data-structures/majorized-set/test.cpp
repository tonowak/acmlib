#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 100);
	int q = rd(1, 100);
	set<pair<int, int>> cur;
	MajorizedSet<int, int> tes;
	REP (i, q) {
		int a = rd(1, n), b = rd(1, n);
		auto p = cur.begin();
		bool majorized = false;
		while (p != cur.end()) {
			auto [x, y] = *p;
			if (x >= a && y >= b) {
				majorized = true;
				break;
			}
			if (x <= a && y <= b) {
				p = cur.erase(p);
				continue;
			}
			++p;
		}
		if (!majorized)
			cur.emplace(a, b);
		tes.insert(pair(a, b));
		assert(tes.s == cur);
	}
}
