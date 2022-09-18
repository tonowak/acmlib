#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto get_vec = [&] {
		int n = rd(0, 20);
		vector<int> v(n);
		for(int &e : v)
			e = rd(0, mod - 1);
		return v;
	};
	auto a = get_vec();
	auto b = get_vec();
	auto c = conv(a, b);
	vector<int> d(max(0, ssize(a) + ssize(b) - 1));
	for(int i = 0; i < ssize(a); ++i)
		for(int j = 0; j < ssize(b); ++j)
			d[i + j] = add(d[i + j], mul(a[i], b[j]));
	int s = max(ssize(c), ssize(d));
	c.resize(s), d.resize(s);
	assert(c == d);
}
