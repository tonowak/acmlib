#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	const int mn = 50;
	const int mk = 50;
	const int ma = 100;

	int n = rd(0, mn);
	int k = rd(0, mk);

	int limit = max(n, k);
	vector<int> fact(limit + 1, 1), rev(limit + 1, 1);
	FOR(i, 1, limit)
		fact[i] = mul(fact[i - 1], i);
	rev[limit] = inv(fact[limit]);
	for(int i = limit; i > 0; --i)
		rev[i - 1] = mul(rev[i], i);
	auto newton = [&](int a, int b) {
		if (a < b or b < 0)
			return 0;
		return mul(fact[a], mul(rev[b], rev[a - b]));
	};

	int a;
	do {
		if(rd(0, 1))
			a = rd(0, min(mod - 1, ma));
		else
			a = rd(0, mod - 1);
	} while(a == 1);

	int brute_monomial = 0;
	int brute_binomial = 0;
	REP(i, n) {
		brute_monomial = add(brute_monomial, mul(powi(a, i), powi(i, k)));
		brute_binomial = add(brute_binomial, mul(powi(a, i), newton(i, k)));
	}
	debug(a, k, n, brute_monomial, brute_binomial);

	assert(brute_monomial == power_monomial_sum(a, k, n));
	assert(brute_binomial == power_binomial_sum(a, k, n));
}
