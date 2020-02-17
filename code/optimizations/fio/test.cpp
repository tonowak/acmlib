#include "main.cpp"
#include "../../utils/testing/test-wrapper.cpp"

bool test(int) {
	freopen("t.in", "r", stdin);
	for(int i = 10; i > 0; --i)
		assert(fastin() == i);
}
