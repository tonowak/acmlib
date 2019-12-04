#include "../../utils/testing/test-wrapper.cpp"
#include "../../utils/headers/main.cpp"
#include "main.cpp"

bool test(int) {
	LL p;
	while(true) {
		p = rd(2, 15);
		if(miller_rabin(p))
			break;
	} 
	int b = primitive_root(p); int k = rd(1, p - 1);
	int a = exp(b, k, p);
	debug(p, b, k, a);
	int out = discrete_root(a, k, p);
	debug(p, a, k, b, out);
	assert(b == out);
	return false;
}

