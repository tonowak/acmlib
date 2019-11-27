/* 
 * Opis: Wzór na całkę z zasady Simpsona. 
 * Daj asserta na błąd, zwiększ n
 */

using T = double;
T intergral(function<T(T)> f, T a, T b) {
	const int n = 1000;
	T delta = (b - a) / n, sum = f(a) + f(b);
	FOR(i, 1, 2 * n - 1) 
		sum += f(a + i * delta) * (i & 1 ? 4 : 2);
	return sum * dif / 3;
}
