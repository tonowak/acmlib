/*
 * Opis: O(n),
 *   \texttt{sieve(n)} przetwarza liczby do $n$ włącznie,
 *   \texttt{comp[i]} oznacza czy $i$ jest złożone,
 *   \texttt{prime} zawiera wszystkie liczby pierwsze \texttt{<= n},
 *   na moim kompie dla $n = 1e8$ działa w 0.7s.
 */
vector<bool> comp;
vector<int> prime;
void sieve(int n) {
	prime.clear();
	comp.assign(n + 1, false);
	FOR(i, 2, n) {
		if(!comp[i]) prime.emplace_back(i);
		REP(j, ssize(prime)) {
			if(i * prime[j] > n) break;
			comp[i * prime[j]] = true;
			if(i % prime[j] == 0) break;
		}
	}
}
