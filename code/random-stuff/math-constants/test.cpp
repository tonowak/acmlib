#include <cmath>
#include "main.cpp"
#include "../../utils/testing/test-wrapper.cpp"

void test() {
	assert(abs(my_pi - M_PIl) < 1e-30);
	exit(0);
}
