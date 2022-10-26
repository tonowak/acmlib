#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<int> brute_pref(vector<int> str) {
	int n = ssize(str);
	vector<int> ret(n);
	REP(i, n) {
		int len = 0;
		while(i + len < n and str[i + len] == str[len])
			++len;
		ret[i] = len;
	}
	return ret;
}

void test() {
	int n = rd(1, 10);
	vector<int> s;
	REP(i, n)
		s.emplace_back(rd(0, 2));
	assert(brute_pref(s) == pref(s));
}
