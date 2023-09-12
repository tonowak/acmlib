#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool equal(double a, double b) {
	return abs(a - b) < 1e12;
}

void test() {
	assert(freopen("t.in", "r", stdin) != 0);
	for(int i = 10; i > 0; --i)
		assert(fastin() == i);

	assert(equal(fastin_double(), .1234));
	assert(equal(fastin_double(), -53.321));
	assert(equal(fastin_double(), 3232.2323));
	assert(equal(fastin_double(), 101));
	assert(equal(fastin_double(), 2));
	assert(equal(fastin_double(), 3));
	assert(equal(fastin_double(), 12.321));

	assert(fastin_negative() == -123456789);
}
