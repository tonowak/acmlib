#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

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
	for (int& e : text) e = rd(-1, 2);
	for (int& e : pattern) e = rd(-1, 2);
	debug(text, pattern, brute(text, pattern));
	assert(brute(text, pattern) == wildcard_matching(text, pattern));
}
