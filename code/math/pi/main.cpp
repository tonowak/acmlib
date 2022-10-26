/*
 * Opis: Funkcja pi(n) - liczba liczb pierwszych na przedziale [1..n]
 * Czas: O(n ^ 3/4)
 * Użycie:
 *   Pi pi(n);
 *   pi.query(d); // d musi być dzielnikiem n
 */

struct Pi {
	vector<LL> w, dp;
	int id(LL v) {
		if (v <= w.back() / v)
			return int(v - 1);
		return ssize(w) - int(w.back() / v);
	}
	Pi(LL n) {
		for (LL i = 1; i * i <= n; ++i) {
			w.push_back(i);
			if (n / i != i)
				w.emplace_back(n / i);
		}
		sort(w.begin(), w.end());
		for (LL i : w)
			dp.emplace_back(i - 1);
		for (LL i = 1; (i + 1) * (i + 1) <= n; ++i) {
			if (dp[i] == dp[i - 1])
				continue;
			for (int j = ssize(w) - 1; w[j] >= (i + 1) * (i + 1); --j)
				dp[j] -= dp[id(w[j] / (i + 1))] - dp[i - 1];
		}
	}
	LL query(LL v) {
		assert(w.back() % v == 0);
		return dp[id(v)];
	}
};
