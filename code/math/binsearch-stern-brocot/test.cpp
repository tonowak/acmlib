#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	LL max_value = rd(0, 1) ? LL(1e1) : rd(0, 1) ? LL(4e2) : LL(1e18);
	long double ld = uniform_real_distribution<long double>(0, max_value + 1)(rng);
	debug(max_value, ld);
	auto is_good = [&](pair<LL, LL> p) {
		assert(p.second > 0);
		assert(p.first >= 0);
		return p.first / (long double)(p.second) <= ld;
	};
	pair<LL, LL> found = binsearch(max_value, is_good);

	if(max_value == LL(1e18))
		return;

	vector<pair<LL, LL>> possible;
	FOR(a, 0, max_value)
		FOR(b, 1, max_value)
			if(is_good(pair(a, b)) and __gcd(a, b) == 1)
				possible.emplace_back(pair(a, b));
	sort(possible.begin(), possible.end(), [&](pair<LL, LL> l, pair<LL, LL> r) {
		return l.first / (long double)(l.second) < r.first / (long double)(r.second);
	});
	pair<LL, LL> best = possible.back();
	debug(best, found);
	assert(best == found);
	assert(__gcd(found.first, found.second) == 1);
	assert(found.first >= 0 and found.second > 0);
}
