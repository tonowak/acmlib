#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 17);
	int op_cnt = rd(1, 100);
	if(rd(0, 1)) {
		Tree_Get_Max tree(n);
		vector<int> brute(n);
		while(op_cnt --> 0) {
			int l = rd(0, n - 1), r = rd(0, n - 1);
			if(l > r)
				swap(l, r);
			if(rd(0, 1)) {
				int val = rd(0, 10);
				tree.update(l, val);
				brute[l] = val;
			}
			else {
				int mx = 0;
				FOR(i, l, r)
					mx = max(mx, brute[i]);
				assert(mx == tree.get(l, r));
			}
		}
	}
	else {
		Tree_Update_Max_On_Interval tree(n);
		vector<int> brute(n);
		while(op_cnt --> 0) {
			int l = rd(0, n - 1), r = rd(0, n - 1);
			if(l > r)
				swap(l, r);
			if(rd(0, 1)) {
				int val = rd(0, 10);
				tree.update(l, r, val);
				FOR(i, l, r)
					brute[i] = max(brute[i], val);
			}
			else {
				assert(brute[l] == tree.get(l));
			}
		}
	}
}
