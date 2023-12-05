#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(2, 3);
	vector<P> in(n);
	for(auto &p : in)
		p = P(rd(-10, 10), rd(-10, 10));
	debug(in);

	auto [wzorc0, wzorc1] = furthest_pair(in);
	D wzorc = dist(wzorc0, wzorc1);

	D brute = -1;
	REP(i, n)
		REP(j, i)
			brute = max(brute, dist(in[i], in[j]));
	debug(wzorc, brute);

	assert(abs(wzorc - brute) < eps);
}
