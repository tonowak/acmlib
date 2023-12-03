#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 10);
	int alph = rd(1, 26);
	vector<int> s(n);
	for(int &si : s)
		si = rd(0, alph - 1);
	debug(s);

	auto is_palindrome = [&](int l, int r) {
		FOR(i, l, r)
			if(s[i] != s[r - (i - l)])
				return false;
		return true;
	};

	for(bool only_even_lens : {false, true}) {
		vector<Dp> dp = palindromic_split_dp(s, only_even_lens);

		vector<int> dp_min(n, n + 1);
		REP(r, n)
			FOR(l, 0, r)
				if(is_palindrome(l, r) and (not only_even_lens or (r - l + 1) % 2 == 0))
					dp_min[r] = min(dp_min[r], (l == 0 ? 0 : dp_min[l - 1]) + 1);
		REP(i, n) {
			if(only_even_lens and i % 2 == 0)
				assert(dp[i].mn == n + 1);
			assert(dp[i].mn == dp_min[i]);
		}

		vector<int> dp_count(n);
		REP(r, n)
			FOR(l, 0, r)
				if(is_palindrome(l, r) and (not only_even_lens or (r - l + 1) % 2 == 0))
					dp_count[r] += (l == 0 ? 1 : dp_count[l - 1]);
		REP(i, n) {
			if(only_even_lens and i % 2 == 0)
				assert(dp[i].cnt == 0);
			assert(dp[i].cnt == dp_count[i]);
		}

		REP(i, n)
			debug(i, dp[i].mn_i);
		auto pairs = construct_min_palindromic_split(dp);
		if(dp.back().mn == n + 1) {
			assert(pairs.empty());
			continue;
		}
		debug(pairs);
		vector<int> covered(n);
		for(auto [l, r] : pairs)
			FOR(i, l, r)
				++covered[i];
		REP(i, n)
			assert(covered[i] == 1);
		REP(i, ssize(pairs) - 1)
			assert(pairs[i].second < pairs[i + 1].first);
		for(auto [l, r] : pairs) {
			debug(l, r);
			assert(is_palindrome(l, r));
		}
		assert(ssize(pairs) == dp.back().mn);
	}
}
