/* 
 * Opis : NIE DZIAŁA!
 * Dla piewrszego $p$ oraz $a \perp p, k$ znajduje
 * $b$ takie, że $b^k = a$ (pierwiastek k-tego stopnia z $a$) 
*/

#include "../primitive-root/main.cpp"
#include "../discrete-log/main.cpp"

LL discrete_root(LL a, LL k, LL p) {
	LL g = primitive_root(p);
	LL m = discrete_log(g, a, p);
    LL inv = exp(k, p - 2, p);
	return m * inv % p;
}

