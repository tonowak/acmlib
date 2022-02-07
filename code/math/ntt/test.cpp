#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	mod = 998'244'353;
	auto get_vec = [&] {
		int n = rd(1, 20);
		vector<int> v(n);
		for(int &vi : v)
			vi = rd(0, mod - 1);
		return v;
	};
	auto a = get_vec();
	auto b = get_vec();
	auto c = conv(a, b);
	vector<int> d(ssize(a) + ssize(b) - 1);
	for(int i = 0; i < ssize(a); ++i)
		for(int j = 0; j < ssize(b); ++j)
			d[i + j] = add(d[i + j], mul(a[i], b[j]));
	assert(c == d);
}
