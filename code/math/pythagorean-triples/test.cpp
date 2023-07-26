#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
auto&operator<<(ostream&o,tuple<auto,auto,auto>t){return o<<"("<<get<0>(t)<<", "<<get<1>(t)<<", "<<get<2>(t)<<")";}

void test() {
	int limit = rd(0, 1e3);
	auto vec = pythagorean_triples(limit);
	debug(limit, vec);

	for (auto [a, b, c] : vec)
		assert(LL(a) * a + LL(b) * b == LL(c) * c);

	set<tuple<int, int, int>> s;
	auto add = [&](int a, int b, int c) {
		assert(s.find({a, b, c}) == s.end());
		s.emplace(a, b, c);
	};
	for (auto [a, b, c] : vec) {
		add(a, b, c);
		add(b, a, c);
	}
	FOR(a, 1, limit) {
		FOR(b, 1, limit) {
			int c = int(sqrt(LL(a) * a + LL(b) * b));
			if (c > limit)
				break;
			if (LL(a) * a + LL(b) * b != LL(c) * c)
				continue;
			if (gcd(gcd(a, b), c) != 1)
				continue;
			assert(s.find({a, b, c}) != s.end());
		}
	}
}
