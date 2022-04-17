#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	Fenwick fenwick(n);
	vector<int> brute(n);
	REP(op, 20)
		if(rd(0, 1)) {
			int i = rd(0, n - 1);
			int val = rd(-10, 10);
			fenwick.update(i, val);
			brute[i] += val;
		}
		else {
			int l = rd(0, n - 1), r = rd(0, n - 1);
			if(l > r)
				swap(l, r);
			LL sum = 0;
			FOR(i, l, r)
				sum += brute[i];
			assert(sum == fenwick.query(l, r));
		}
}

