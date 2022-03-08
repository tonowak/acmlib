#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

int knapsack_brute(vector<int> w, int bound) {
	int ans = 0;
	REP(mask, 1 << ssize(w)) {
		int sum = 0;
		REP(i, ssize(w))
			if((mask >> i) & 1)
				sum += w[i];
		if(sum <= bound)
			ans = max(ans, sum);
	}
	return ans;
}

void test() {
	int n = rd(0, 15);
	vector<int> w(n);
	for(int &wi : w)
		wi = rd(0, 30);
	int bound = rd(0, ssize(w) * 30);

	LL ans_wzorc = knapsack(w, bound);
	LL ans_brute = knapsack_brute(w, bound);
	assert(ans_wzorc == ans_brute);
}
