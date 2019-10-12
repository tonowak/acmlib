/*
 * Opis: Chińskie Twierdzenie o Resztach
 * Czas: O(\log n)
 * Pamięć : O(1)
 * Użycie:
 *   crt(a, m, b, n) zwraca takie x, że x mod m = a i x mod n = b
 *   m i n nie muszą być wzlędnie pierwsze, ale może nie być wtedy rozwiązania
 *   uwali się wtedy assercik, można zmienić na return -1
 */

tuple<LL, LL, LL> extendedGcd(LL a, LL b) {
	if(a == 0)
		return {b, 0, 1};
	LL x, y, nwd;
	tie(nwd, x, y) = extendedGcd(b % a, a);
	return {nwd, y - x * (b / a), x};
}

LL crt(LL a, LL m, LL b, LL n)
{
	if(n > m) swap(a, b), swap(m, n);
	LL d, x, y;
	tie(d, x, y) = extendedGcd(m, n);
	assert((a - b) % d == 0); 
	LL ret = (b - a) % n * x % n / d * m + a;
	return ret < 0 ? ret + m * n / d : ret;
}
