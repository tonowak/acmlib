#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	RangeAdd tree(n);
	vector<int> brute(n);
	REP(op, 20)
		if(rd(0, 1)) {
			int i = rd(0, n - 1);
			assert(brute[i] == tree.query(i));
		}
		else {
			int l = rd(0, n - 1), r = rd(0, n - 1), val = rd(-10, 10);
			if(l > r)
				swap(l, r);
			FOR(i, l, r)
				brute[i] += val;
			tree.update(l, r, val);
		}
}
