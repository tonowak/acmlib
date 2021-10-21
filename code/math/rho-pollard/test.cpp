#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto f = [&](LL n) {
		vector<LL> v;
		for (LL d = 2; d * d <= n; ++d) {
			while (n % d == 0) {
				n /= d;
				v.emplace_back(d);
			}
		}
		if (n > 1) v.emplace_back(n);
		return v;
	};
	LL mn = (1ll << 40);
	LL n = rd_ll(1, mn);
	vector<LL> vrho = factor(n);
	sort(vrho.begin(), vrho.end());
	vector<LL> vbrute = f(n);
	sort(vbrute.begin(), vbrute.end());
	assert(vrho == vbrute);
}
