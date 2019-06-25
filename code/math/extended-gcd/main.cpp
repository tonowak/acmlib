/**
 * Description: Dla danego $(a, b)$ znajduje 
 *   takie $(gcd(a, b), x, y)$, że $ax + by = gcd(a, b)$
 * Time: O(\log(\max(a, b)))
 * Memory: same
 * Usage:
 *  int gcd, x, y;
 *  tie(gcd, x, y) = extendedGcd(a, b);
 */

tuple<LL, LL, LL> extendedGcd(LL a, LL b) {
	if(a == 0)
		return {b, 0, 1};
	LL x, y, nwd;
	tie(nwd, x, y) = extendedGcd(b % a, a);
	return {nwd, y - x * (b / a), x};
}

