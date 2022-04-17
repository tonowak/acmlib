#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<int> brute_conv_mod(vector<int> a, vector<int> b, int mod) {
	if(ssize(a) == 0 or ssize(b) == 0)
		return {};
	vector<int> res(ssize(a) + ssize(b) - 1);
	REP(i, ssize(a))
		REP(j, ssize(b))
			res[i + j] = int((res[i + j] + a[i] * LL(b[j])) % mod);
	return res;
}

void test() {
	constexpr int mod = int(1e9) + 7;
	auto get_random_v = [&] {
		vector<int> ret(rd(0, 500));
		for(int &x : ret)
			x = rd(0, mod - 1);
		return ret;
	};
	vector a = get_random_v();
	vector b = get_random_v();
	debug(a, b);
	debug(conv_mod(a, b, mod));
	debug(brute_conv_mod(a, b, mod));
	assert(conv_mod(a, b, mod) == brute_conv_mod(a, b, mod));
}
