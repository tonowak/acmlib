/*
 * Opis: Binsearch na ułamkach.
 * Czas: O(\log max\_val)
 * Użycie:
 *   Szuka największego a/b, że is_ok(a/b) oraz 0 <= a,b <= max_value. Zakłada, że is_ok(0) == true.
 */
using Frac = pair<LL, LL>;
Frac my_max(Frac l, Frac r) {
	return l.first * __int128_t(r.second) > r.first * __int128_t(l.second) ? l : r;
}
Frac binsearch(LL max_value, function<bool (Frac)> is_ok) {
	assert(is_ok(pair(0, 1)) == true);
	Frac left = {0, 1}, right = {1, 0}, best_found = left;
	int current_dir = 0;
	while(max(left.first, left.second) <= max_value) {
		best_found = my_max(best_found, left);
		auto get_frac = [&](LL mul) {
			LL mull = current_dir ? 1 : mul;
			LL mulr = current_dir ? mul : 1;
			return pair(left.first * mull + right.first * mulr, left.second * mull + right.second * mulr);
		};
		auto is_good_mul = [&](LL mul) {
			Frac mid = get_frac(mul);
			return is_ok(mid) == current_dir and max(mid.first, mid.second) <= max_value;
		};
		LL power = 1;
		for(; is_good_mul(power); power *= 2) {}
		LL bl = power / 2 + 1, br = power;
		while(bl != br) {
			LL bm = (bl + br) / 2;
			if(not is_good_mul(bm))
				br = bm;
			else
				bl = bm + 1;
		}
		tie(left, right) = pair(get_frac(bl - 1), get_frac(bl));
		if(current_dir == 0)
			swap(left, right);
		current_dir ^= 1;
	}
	return best_found;
}
