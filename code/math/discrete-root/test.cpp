#include "../../utils/testing/test-wrapper.cpp"
#define CHANGABLE_MOD
#include "main.cpp"

void test() {
	while(true) {
		mod = rd(2, int(1e5));
		if(miller_rabin(mod))
			break;
	}
	int k = rd(0, mod - 2);
	int a = rd(1, mod - 1);
	int x = discrete_root(a, k);
	debug(mod, k, a, x);
	if(x == -1)
		return;
	assert(powi(x, k) == a);
}

