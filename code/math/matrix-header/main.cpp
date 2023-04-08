/*
 * Opis: Funkcje pomocnicze do algorytmów macierzowych.
 */

#if 1
constexpr int mod = 998'244'353;
bool equal(int a, int b) {
	return a == b;
}
int mul(int a, int b) {
	return int(a * LL(b) % mod);
}
int add(int a, int b) {
	a += b;
	return a >= mod ? a - mod : a;
}
int powi(int a, int b) {
	for(int ret = 1;; b /= 2) {
		if(b == 0)
			return ret;
		if(b & 1)
			ret = mul(ret, a);
		a = mul(a, a);
	}
}
int inv(int x) {
	return powi(x, mod - 2);
}
int divide(int a, int b) {
	return mul(a, inv(b));
}
int sub(int a, int b) {
	return add(a, mod - b);
}
using T = int;
#else
constexpr double eps = 1e-9;
bool equal(double a, double b) {
	return abs(a - b) < eps;
}
#define OP(name, op) double name(double a, double b) { return a op b; }
OP(mul, *)
OP(add, +)
OP(divide, /)
OP(sub, -)
using T = double;
#endif
