#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<pair<int, int>> ranges_of_values(vector<int> in) {
	if(in.empty())
		return {};
	vector<pair<int, int>> ret = {{in[0], in[0]}};
	FOR(i, 1, ssize(in) - 1)
		if(in[i] == in[i - 1] + 1)
			ret.back().second += 1;
		else
			ret.emplace_back(in[i], in[i]);
	return ret;
}

vector<tuple<int, int, int>> brute_squares(vector<int> str) {
	int n = ssize(str);
	vector<tuple<int, int, int>> ret;
	FOR(len, 1, n / 2) {
		vector<int> good_starts;
		REP(start, n - 2 * len + 1) {
			vector<int> substr;
			REP(i, 2 * len)
				substr.emplace_back(str[i + start]);
			bool valid = true;
			REP(i, len)
				if(substr[i] != substr[i + len])
					valid = false;
			if(valid)
				good_starts.emplace_back(start);
		}
		for(auto [l, r] : ranges_of_values(good_starts))
			ret.emplace_back(l, r, len);
	}
	return ret;
}

void test() {
	static bool was_maxtest = false;
	int n = was_maxtest ? rd(1, 10) : int(1e5);
	vector<int> s;
	REP(i, n)
		s.emplace_back(rd(0, 2));
	debug(n, s);

	auto wzorc = squares(s);
	if(was_maxtest) {
		auto brute = brute_squares(s);
		sort(brute.begin(), brute.end());
		sort(wzorc.begin(), wzorc.end());
		assert(brute == wzorc);
	}
	was_maxtest = true;
}
