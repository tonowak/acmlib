#include "main.cpp"

int main() {
	REP(i, 1000) {
		LL limit = LL(1e18);
		LL a = rd(-limit, limit), b = rd(-limit, limit);
		LL good_gcd = __gcd(a, b);
		LL gcd, x, y;
		tie(gcd, x, y) = extendedGcd(a, b);
		assert(gcd == good_gcd);
		// assert(a * x + b * y == gcd);
	}
}
