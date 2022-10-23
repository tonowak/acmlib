#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 17);
	Tree tree(n);
	vector<LL> brute(n);
	int op_cnt = rd(1, 100);
	while(op_cnt --> 0) {
		if(rd(0, 1)) {
			int l = rd(0, n - 1), r = rd(0, n - 1);
			if(l > r)
				swap(l, r);
			LL sum_brute = 0;
			FOR(i, l, r)
				sum_brute += brute[i];
			assert(sum_brute == tree.get(l, r).sum);
		}
		else {
			int l = rd(0, n - 1), r = rd(0, n - 1);
			if(l > r)
				swap(l, r);
			int val = rd(-10, 10);
			FOR(i, l, r)
				brute[i] += val;
			tree.update(l, r, val);
		}
	}
}
