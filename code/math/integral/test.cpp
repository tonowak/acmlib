#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int a = rd(-5, 5), b = rd(-5, 5), c = rd(-5, 5);
	auto f = [&](D x) {
		return x * x * a + x * b + c;
	};
	D l = rd(-5, 5), r = rd(-5, 5);
	if(l > r)
		swap(l, r);
	D wzorc = integrate(f, l, r);
	auto fp = [&](D x) {
		return x * x * x * a / 3 + x * x * b / 2 + x * c;
	};
	D brute = fp(r) - fp(l);
	assert(abs(wzorc - brute) < 1e-8);
}
