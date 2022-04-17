#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	assert(freopen("t.in", "r", stdin) != 0);
	for(int i = 10; i > 0; --i)
		assert(fastin() == i);
}
