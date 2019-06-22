// Chińskie Twierdzenie o Resztach
// crt(a, n, b, m) zwraca taką liczbę x, 
// że x mod n = a i x mod m = b
// m i n nie muszą być względnie pierwsze, ale wtedy może nie być rozwiązania
// (jest na to assercik)

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
