#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool covers(vector<int> s, vector<int> base) {
	set<int> ss(s.begin(), s.end());
	REP(mask, 1 << ssize(base)) {
		int ksor = 0;
		REP(i, ssize(base))
			if((mask >> i) & 1)
				ksor ^= base[i];
		auto it = ss.find(ksor);
		if(it != ss.end())
			ss.erase(it);
	}
	return ss.empty();
}

int get_base_size(vector<int> s) {
	int ans = ssize(s);
	REP(mask, 1 << ssize(s)) {
		vector<int> base;
		REP(i, ssize(s))
			if((mask >> i) & 1)
				base.emplace_back(s[i]);
		if(covers(s, base))
			ans = min(ans, ssize(base));
	}
	return ans;
}

void test() {
	int n = rd(1, 9);
	int gen_bits = rd(1, 4);
	vector<int> s(n);
	for(int &si : s)
		si = rd(0, (1 << gen_bits) - 1);

	vector<int> base = xor_base(s);
	assert(ssize(base) == get_base_size(s));
	assert(covers(s, base));
}
