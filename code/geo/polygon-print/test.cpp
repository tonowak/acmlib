#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
#define rng rng_wrapper
#define rd rd_wrapper
#include "../polygon-gen/main.cpp"
#undef rng
#undef rd


void test() {
	/*
    auto v = gen_polygon(8, 8);
    debug(v);
    polygon_print(v, 10);
	exit(0);
	*/
}

