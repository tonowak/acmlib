#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int test_type = (rd(0, 100) > 0 ? 0 : 1);
	int max_n = (test_type == 0 ? 7 : 100);
	int n0 = rd(1, max_n);
	int n1 = rd(1, max_n);
	if(n0 > n1)
		swap(n0, n1);
	int max_weight = (rd(0, 1) ? 10 : int(1e9));
	vector<vector<int>> weight(n0, vector<int>(n1));
	REP(i, n0)
		REP(j, n1)
			weight[i][j] = rd(-max_weight, max_weight);

	auto [ans, match] = hungarian(weight);
	vector<bool> used_in_m(n1, false);
	for(int i : match) {
		assert(not used_in_m[i]);
		used_in_m[i] = true;
	}
	LL ans_check = 0;
	REP(i, n0)
		ans_check += weight[i][match[i]];
	assert(ans == ans_check);

	if(test_type == 0) {
		LL ans_brute = LL(1e18);
		vector<int> perm(n1);
		iota(perm.begin(), perm.end(), 0);
		do {
			vector<int> brute_match = perm;
			brute_match.resize(n0);
			LL ans_local = 0;
			REP(i, n0)
				ans_local += weight[i][brute_match[i]];
			ans_brute = min(ans_brute, ans_local);
		} while(next_permutation(perm.begin(), perm.end()));
		assert(ans == ans_brute);
	}
}
