/* 
 * Opis: O(idk), zwraca całkę f na [l, r].
 */
using D = long double;
D simpson(function<D (D)> f, D l, D r) {
	return (f(l) + 4 * f((l + r) / 2) + f(r)) * (r - l) / 6;
}
D integrate(function<D (D)> f, D l, D r, D s, D eps) {
	D m = (l + r) / 2;
	D sl = simpson(f, l, m), sr = simpson(f, m, r), s2 = sl + sr;
	if(abs(s2 - s) < 15 * eps or r - l < 1e-10)
		return s2 + (s2 - s) / 15;
	return integrate(f, l, m, sl, eps / 2)
		+ integrate(f, m, r, sr, eps / 2);
}
D integrate(function<D (D)> f, D l, D r) {
	return integrate(f, l, r, simpson(f, l, r), 1e-8);
}
