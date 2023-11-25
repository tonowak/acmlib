/*
 * Opis: O(\log n),
 *   \texttt{pell(n)} oblicza rozwiązanie fundamentalne $x^2-ny^2=1$,
 *   zwraca $(0, 0)$ jeżeli nie istnieje ($n$ jest kwadratem lub wynik przekracza LL),
 *   \texttt{all\_pell(n, limit)} wyznacza wszystkie rozwiązania $x^2-ny^2=1$ z $x\le \texttt{limit}$,
 *   w razie potrzeby można przepisać na pythona lub użyć bignumów.
 */
pair<LL, LL> pell(LL n) {
	LL s = LL(sqrtl(n));
	if (s * s == n) return {0, 0};
	LL m = 0, d = 1, a = s;
	__int128 num1 = 1, num2 = a, den1 = 0, den2 = 1;
	while (num2 * num2 - n * den2 * den2 != 1) {
		m = d * a - m;
		d = (n - m * m) / d;
		a = (s + m) / d;
		if (num2 > (1ll << 62) / a) return {0, 0};
		tie(num1, num2) = pair(num2, a * num2 + num1);
		tie(den1, den2) = pair(den2, a * den2 + den1);
	}
	return {num2, den2};
}
vector<pair<LL, LL>> all_pell(LL n, LL limit) {
	auto [x0, y0] = pell(n);
	if (!x0) return {};
	vector<pair<LL, LL>> ret;
	__int128 x = x0, y = y0;
	while (x <= limit) {
		ret.emplace_back(x, y);
		if (y0 * y > (1ll << 62) / n) break;
		tie(x, y) = pair(x0 * x + n * y0 * y, x0 * y + y0 * x);
	}
	return ret;
}
