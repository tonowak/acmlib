#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	mod = int(1e9) + 7;
	assert(add(mod - 1, mod - 1) == mod - 2);
	assert(sub(0, mod - 1) == 1);
	assert(sub(mod - 1, 0) == mod - 1);
	assert(sub(mod - 1, mod - 1) == 0);
	assert(mul(mod - 1, mod - 1) == 1);
	FOR(i, 1, 100) {
		assert(mul(inv(i), i) == 1);
		assert(mul(inv(mod - i), mod - i) == 1);
	}
	exit(0);
}
