#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

using PII = pair<int, int>;
#define ST first
#define ND second

bool test(int ms) {
	vector<PII> f;
	auto eval = [&](PII p, int x) { return p.ST * x + p.ND; };
	auto get = [&](int x) {
		int ret = -1e9;
		for(PII &p : f) ret = max(ret, eval(p, x));
		return ret;
	};

	LineContainer lc;

	int n = rd(1, 1000);
	REP(i, n) {
		if(i == 0 || rd(0, 1)) {
			int a = rd(-100, 100);
			int b = rd(-1000, 1000);
			f.emplace_back(a, b);
			lc.add(a, b);
		}
		else {
			int x = rd(-1000, 1000);
			if(get(x) != lc.query(x))
				return true;
		}
	}

	return false;
}
