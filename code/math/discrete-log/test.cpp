#include "../../utils/testing/test-wrapper.cpp"
#include "../../utils/headers/main.cpp"
#include "../primitive-root/main.cpp"
#include "main.cpp"

void test() {
	LL p;
	while(true) {
		p = rd(2, 100000000);
		if(miller_rabin(p))
			break;
	} 
	int a = primitive_root(p); int b = rd(1, p - 1);
	int e = discrete_log(a, b, p);
	debug(p, a, b, e);
	assert(exp(a, e, p) == b);
}

