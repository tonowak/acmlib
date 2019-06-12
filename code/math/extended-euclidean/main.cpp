#include "../../utils/headers/main.cpp"

tuple<LL, LL, LL> extendedGcd(LL a, LL b) {
	if(a == 0)
		return {b, 0, 1};
	LL x, y, nwd;
	tie(nwd, x, y) = extendedGcd(b % a, a);
	return {nwd, y - x * (b / a), x};
}

