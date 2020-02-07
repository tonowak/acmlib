/*
 * Opis: Liczy $a^b$ modulo $m$ (dla $m < 10^9$)
 * Czas: O(\log(b))
 */

LL exp(LL a, LL b, LL m) {
	if(b == 0) return 1;
	if(b & 1) return a * exp(a, b - 1, m) % m;
	LL t = exp(a, b / 2, m);
	return t * t % m;
} 
