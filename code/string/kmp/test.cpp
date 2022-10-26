#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool is_border(vector<int> s, int len) {
	if(len >= ssize(s))
		return false;
	if(len == 0)
		return true;
	return vector(s.begin(), s.begin() + len) == vector(s.begin() + ssize(s) - len, s.end());
}

void test() {
	int n = rd(1, 20);
	vector<int> s;
	REP(i, n)
		s.emplace_back(rd(0, 2));

	vector kmp = get_kmp(s);
	REP(i, n) {
		int found_len = 0;
		for(int len = i; len >= 0; --len)
			if(is_border(vector(s.begin(), s.begin() + i + 1), len)) {
				found_len = len;
				break;
			}
		assert(kmp[i] == found_len);
	}
	vector<int> borders;
	FOR(len, 1, n)
		if(len == n or is_border(s, len))
			borders.emplace_back(len);
	assert(borders == get_borders(s));
}
