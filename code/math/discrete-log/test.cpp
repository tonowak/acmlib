#include "../../utils/testing/test-wrapper.cpp"
#define CHANGABLE_MOD
#include "../primitive-root/main.cpp"
#include "main.cpp"

void test() {
	while(true) {
		mod = rd(2, int(1e9));
		if(miller_rabin(mod))
			break;
	} 
	int a = primitive_root(); 
	int b = rd(1, mod - 1);
	int e = discrete_log(a, b);
	debug(mod, a, b, e);
	if(e == -1)
		return;
	assert(powi(a, e) == b);
}

