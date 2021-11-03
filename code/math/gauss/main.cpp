/*
 * Opis: Rozwiązywanie układów liniowych (modint albo double) NIEPRZETESTOWANE
 * Czas: O(nm(n + m))
 * Użycie: Wrzucam n vectorów {wsp_x0, wsp_x1, ..., wsp_xm, suma},
 *   gauss wtedy zwraca liczbę rozwiązań
 *   (0, 1 albo 2 (tzn. nieskończoność))
 *   oraz jedno poprawne rozwiązanie (o ile istnieje).
 *   Przykład - gauss({2, -1, 1, 7}, {1, 1, 1, 1}, {0, 1, -1, 6.5})
 *   zwraca (1, {6.75, 0.375, -6.125})
 */

#if 0
bool equal(int a, int b) {
	return a == b;
}
constexpr int mod = int(1e9) + 7;
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

pair<int, vector<T>> gauss(vector<vector<T>> a) {
	int n = ssize(a); // liczba wierszy
	int m = ssize(a[0]) - 1; // liczba zmiennych

	vector<int> where(m, -1); // w ktorym wierszu jest zdefiniowana i-ta zmienna
	for(int col = 0, row = 0; col < m and row < n; ++col) {
		int sel = row;
		for(int y = row; y < n; ++y)
			if(abs(a[y][col]) > abs(a[sel][col]))
				sel = y;
		if(equal(a[sel][col], 0))
			continue;
		for(int x = col; x <= m; ++x)
			swap(a[sel][x], a[row][x]);
		// teraz sel jest nieaktualne
		where[col] = row;

		for(int y = 0; y < n; ++y)
			if(y != row) {
				T wspolczynnik = divide(a[y][col], a[row][col]);
				for(int x = col; x <= m; ++x)
					a[y][x] = sub(a[y][x], mul(wspolczynnik, a[row][x]));
			}
		++row;
	}

	vector<T> answer(m);
	for(int col = 0; col < m; ++col)
		if(where[col] != -1)
			answer[col] = divide(a[where[col]][m], a[where[col]][col]);

	for(int row = 0; row < n; ++row) {
		T got = 0;
		for(int col = 0; col < m; ++col)
			got = add(got, mul(answer[col], a[row][col]));
		if(not equal(got, a[row][m]))
			return {0, answer};
	}

	for(int col = 0; col < m; ++col)
		if(where[col] == -1)
			return {2, answer};
	return {1, answer};
}
