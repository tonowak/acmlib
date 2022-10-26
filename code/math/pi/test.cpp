#include "../../utils/testing/test-wrapper.cpp"
#include "../sieve/main.cpp"
#include "main.cpp"

void test() {
	static const int mn = 1e5;
	static vector<int> pref;
	if (pref.empty()) {
		sieve(mn);
		pref.resize(mn + 1);
		FOR(i, 2, mn)
			pref[i] = pref[i - 1] + (not comp[i]);
	}
	int n = rd(1, mn);
	Pi pi(n);
	FOR(i, 1, n) {
		if (n % i)
			continue;
		assert(pref[i] == pi.query(i));
	}
}
