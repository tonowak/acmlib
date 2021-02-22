#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	LL p;
	while(true) {
		p = rd(2, 15);
		if(miller_rabin(p))
			break;
	} 
	int k = rd(0, p - 2);
	int a = rd(1, p - 1);
	int x = discrete_root(a, k, p);
	debug(p, k, a, x);
	assert(exp(x, k, p) == a);
}

