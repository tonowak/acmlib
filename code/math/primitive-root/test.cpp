#include "../../utils/testing/test-wrapper.cpp"
#define CHANGABLE_MOD
#include "main.cpp"

void test() {
	while(true) {
		mod = rd(7, int(1e5));
		if(miller_rabin(mod))
			break;
	}
	int g = primitive_root();
	debug(mod, g);
	set<int> res;
	int mult = 1;
	REP(i, mod - 1) {
		debug(res);
		assert(res.find(mult) == res.end());
		res.insert(mult);
		mult = mul(mult, g);
	}
}
