/*
 * Opis: O(k^n), ciag/cykl de Brujina słów długości $n$ nad alfabetem $\{0, 1, ..., k - 1\}$.
 * Jeżeli \texttt{is\_path} to zwraca ciąg, wpp. zwraca cykl.
 */
#include "../eulerian-path/main.cpp"
vector<int> de_brujin(int k, int n, bool is_path) {
	if (n == 1) {
		vector<int> v(k);
		iota(v.begin(), v.end(), 0);
		return v;
	}
	if (k == 1)
		return vector (n, 0);
	int N = 1;
	REP(i, n - 1)
		N *= k;
	vector<pair<int, int>> edges;
	REP(i, N)
		REP(j, k)
			edges.emplace_back(i, i * k % N + j);
	vector<int> path = get<2>(eulerian_path(N, edges, true));
	path.pop_back();
	for(auto& e : path)
		e = e % k;
	if (is_path)
		REP(i, n - 1)
			path.emplace_back(path[i]);
	return path;
}
