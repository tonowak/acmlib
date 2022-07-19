/*
 * Opis: Dla danego $(a, b)$ znajduje 
 *   takie $(gcd(a, b), x, y)$, że $ax + by = gcd(a, b)$
 * Czas: O(\log(\min(a, b)))
 * Użycie:
 *  auto [gcd, x, y] = extended_gcd(a, b);
 */

tuple<LL, LL, LL> extended_gcd(LL a, LL b) {
	if(a == 0)
		return {b, 0, 1};
	auto [gcd, x, y] = extended_gcd(b % a, a);
	return {gcd, y - x * (b / a), x};
}
