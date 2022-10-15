/*
 * Opis: Wyznacznik macierzy (modulo lub double)
 * Czas: O(n^3)
 * Użycie: determinant(a)
 */

#if 1
constexpr int mod = 998'244'353;
bool equal(int a, int b) {
	return a == b;
}
int mul(int a, int b) {
	return int((a * LL(b)) % mod);
}
int add(int a, int b) {
	a += b;
	return a >= mod ? a - mod : a;
}
int powi(int a, int b) {
	if(b == 0)
		return 1;
	int x = powi(a, b / 2);
	x = mul(x, x);
	if(b % 2 == 1)
		x = mul(x, a);
	return x;
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

T determinant(vector<vector<T>>& a) {
	int n = ssize(a);
	T res = 1;
	REP(i, n) {
		int b = i;
		FOR(j, i + 1, n - 1)
			if(abs(a[j][i]) > abs(a[b][i]))
				b = j;
		if(i != b)
			swap(a[i], a[b]), res = sub(0, res);
		res = mul(res, a[i][i]);
		if (equal(res, 0))
			return 0;
		FOR(j, i + 1, n - 1) {
			T v = divide(a[j][i], a[i][i]);
			if (not equal(v, 0))
				FOR(k, i + 1, n - 1)
					a[j][k] = sub(a[j][k], mul(v, a[i][k]));
		}
	}
	return res;
}
