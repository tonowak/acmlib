#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	vector<int> a(n);
	REP(i,n) a[i] = rd(1, 20);
	RMQ rmq(a);
	REP(i,n) {
		REP(j,i) {
			auto ans = rmq.query(j, i);
			int brute = 1 << 30;
			FOR(k,j,i)
				brute = min(brute, a[k]);
			assert(ans == brute);
		}
	}
}
