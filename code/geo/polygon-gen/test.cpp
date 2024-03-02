#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#define rng rng_wrapper
#define rd rd_wrapper
#include "main.cpp"
#undef rng
#undef rd
#include "../area/main.cpp"

void test() {
	int N = rd(3, 50);
	int z = int(1e5);
	auto v = gen_polygon(N, z);
	assert(area(v) > 0);
}
