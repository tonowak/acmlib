/*
 * Opis: Dla tablicy $A[i]$ oblicza tablicę $F[mask] = \sum_{i\subseteq mask} A[i]$, czyli sumę po podmaskach. Może też liczyć sumę po nadmaskach.
 * Czas: O(n * 2^n)
 * Użycie:
 * sos_dp(n, A, true/false) // $n$ - liczba bitów, $A$ - tablica długości $2^n$, bool - czy po nadmaskach
 * sos_dp(2, {4, 3, 7, 2}) // {4, 7, 11, 16} - po podmaskach
 * sos_dp(2, {4, 3, 7, 2}, true) // {16, 5, 9, 2} - po nadmaskach
 */

vector<LL> sos_dp(int n, vector<LL> A, bool nad = false) {
	int N = (1 << n);
	if (nad) REP(i, N / 2) swap(A[i], A[(N - 1) ^ i]);
	auto F = A;
	REP(i, n)
		REP(mask, N)
			if ((mask >> i) & 1)
				F[mask] += F[mask ^ (1 << i)];
	if (nad) REP(i, N / 2) swap(F[i], F[(N - 1) ^ i]);
	return F;
}
