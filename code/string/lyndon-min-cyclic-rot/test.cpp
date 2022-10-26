#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void assert_is_valid_lyndon_factorization(vector<int> s, vector<pair<int, int>> fact) {
	debug(s, fact);
	REP(i, ssize(fact) - 1)
		assert(fact[i].second + 1 == fact[i + 1].first);
	assert(fact.front().first == 0 and fact.back().second == ssize(s) - 1);
	vector<vector<int>> order;
	for(auto [l, r] : fact) {
		assert(l <= r);
		vector<int> sub(s.begin() + l, s.begin() + r + 1);
		FOR(suff_len, 1, r - l)
			assert(sub < vector(s.begin() + l + (r - l + 1) - suff_len, s.begin() + l + (r - l + 1)));
		order.emplace_back(sub);
	}
	REP(i, ssize(order) - 1)
		assert(order[i] >= order[i + 1]);
}

vector<int> brute_min_cyclic_shift(vector<int> s) {
	int n = ssize(s);
	vector<int> mn = s;
	REP(i, n) {
		vector<int> nw;
		REP(j, n)
			nw.emplace_back(s[(i + j) % n]);
		mn = min(mn, nw);
	}
	return mn;
}

vector<int> brute_min_suffix(vector<int> s) {
	int n = ssize(s);
	vector<int> mn = s;
	REP(i, n)
		mn = min(mn, vector(s.begin() + i, s.end()));
	return mn;
}

void test() {
	auto got = duval({0, 1, 0, 2, 0, 1, 0});
	assert(ssize(got) == 3 and got[0] == pair(0, 3) and got[1] == pair(4, 5) and got[2] == pair(6, 6));
	assert(min_suffix({0, 1, 0, 2, 0, 1}) == (vector{0, 1}));
	assert(min_cyclic_shift({0, 1, 0, 2, 0, 1, 0}) == (vector{0, 0, 1, 0, 2, 0, 1}));

	int n = rd(1, 10), alpha = rd(1, 5);
	vector<int> s;
	REP(i, n)
		s.emplace_back(rd(0, alpha - 1));
	assert(brute_min_cyclic_shift(s) == min_cyclic_shift(s));
	assert_is_valid_lyndon_factorization(s, duval(s));
	assert(brute_min_suffix(s) == min_suffix(s));
}
