#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
//#include "../miller-rabin/main.cpp"

bool test(int) {
	LL p;
	while(true) {
		p = rd(7, 15);
		if(miller_rabin(p))
			break;
	}
	int g = primitive_root(p);
	debug(p, g);
	set<int> res;
	int mult = 1;
	REP(i, p - 1) {
		debug(res);
		assert(res.find(mult) == res.end());
		res.insert(mult);
		mult = mult * g % p;
	}
	return false;
}
