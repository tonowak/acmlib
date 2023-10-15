#include "../../utils/testing/test-wrapper.cpp"
#define rng rng_wrapper
#include "main.cpp"
#undef rng

vector<bool> brute(vector<int> text, vector<int> pattern) {
	const int n = ssize(text);
	const int m = ssize(pattern);
	assert(m <= n);
	vector<bool> ret(n - m + 1);
	REP(i, n - m + 1) {
		bool ok = true;
		REP(j, m) {
			if (text[i + j] != -1 and pattern[j] != -1 and text[i + j] != pattern[j]) {
				ok = false;
				break;
			}
		}
		ret[i] = ok;
	}
	return ret;
}

void test() {
	int n = rd(1, 30);
	int m = rd(1, n);
	vector<int> text(n), pattern(m);
	const int alpha = rd(0, 1) ? 3 : 20;
	for (int& e : text) e = rd(-1, alpha - 1);
	for (int& e : pattern) e = rd(-1, alpha - 1);
	const auto brute_ret = brute(text, pattern);
	debug(text, pattern, brute_ret);
	assert(brute_ret == wildcard_matching(text, pattern));
	assert(brute_ret == safer_wildcard_matching(text, pattern, alpha));
}
