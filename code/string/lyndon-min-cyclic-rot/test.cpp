#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void assert_is_valid_lyndon_factorization(string s, vector<pair<int, int>> fact) {
	debug(s.data(), fact);
	REP(i, ssize(fact) - 1)
		assert(fact[i].second + 1 == fact[i + 1].first);
	assert(fact.front().first == 0 and fact.back().second == ssize(s) - 1);
	vector<string> order;
	for(auto [l, r] : fact) {
		assert(l <= r);
		string sub = s.substr(l, r - l + 1);
		FOR(suff_len, 1, r - l)
			assert(sub < s.substr(l + (r - l + 1) - suff_len, suff_len));
		order.emplace_back(sub);
	}
	REP(i, ssize(order) - 1)
		assert(order[i] >= order[i + 1]);
}

string brute_min_cyclic_shift(string s) {
	int n = ssize(s);
	string mn = s;
	REP(i, n) {
		string nw;
		REP(j, n)
			nw += s[(i + j) % n];
		mn = min(mn, nw);
	}
	return mn;
}

string brute_min_suffix(string s) {
	int n = ssize(s);
	string mn = s;
	REP(i, n)
		mn = min(mn, s.substr(i));
	return mn;
}

void test() {
	auto got = duval("abacaba");
	assert(ssize(got) == 3 and got[0] == pair(0, 3) and got[1] == pair(4, 5) and got[2] == pair(6, 6));
	assert(min_suffix("abacab") == "ab");
	assert(min_cyclic_shift("abacaba") == "aabacab");

	int n = rd(1, 10), alpha = rd(1, 5);
	string s;
	REP(i, n)
		s += char('a' + rd(0, alpha - 1));
	assert(brute_min_cyclic_shift(s) == min_cyclic_shift(s));
	assert_is_valid_lyndon_factorization(s, duval(s));
	assert(brute_min_suffix(s) == min_suffix(s));
}
