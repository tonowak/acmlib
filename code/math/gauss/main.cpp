/*
 * Opis: O(nm(n+m)),
 *   Wrzucam $n$ vectorów \texttt{\{wsp\_x0, wsp\_x1, ..., wsp\_xm - 1, suma\}},
 *   gauss wtedy zwraca liczbę rozwiązań
 *   (0, 1 albo 2 (tzn. nieskończoność))
 *   oraz jedno poprawne rozwiązanie (o ile istnieje).
 *   Przykład \texttt{gauss(\{2, -1, 1, 7\}, \{1, 1, 1, 1\}, \{0, 1, -1, 6.5\})}
 *   zwraca \texttt{(1, \{6.75, 0.375, -6.125\})}.
 */
#include "../matrix-header/main.cpp"
pair<int, vector<T>> gauss(vector<vector<T>> a) {
	int n = ssize(a); // liczba wierszy
	int m = ssize(a[0]) - 1; // liczba zmiennych
	vector<int> where(m, -1); // w ktorym wierszu jest zdefiniowana i-ta zmienna
	for(int col = 0, row = 0; col < m and row < n; ++col) {
		int sel = row;
		for(int y = row; y < n; ++y)
			if(abs(a[y][col]) > abs(a[sel][col]))
				sel = y;
		if(equal(a[sel][col], 0))
			continue;
		for(int x = col; x <= m; ++x)
			swap(a[sel][x], a[row][x]);
		// teraz sel jest nieaktualne
		where[col] = row;
		for(int y = 0; y < n; ++y)
			if(y != row) {
				T wspolczynnik = divide(a[y][col], a[row][col]);
				for(int x = col; x <= m; ++x)
					a[y][x] = sub(a[y][x], mul(wspolczynnik, a[row][x]));
			}
		++row;
	}
	vector<T> answer(m);
	for(int col = 0; col < m; ++col)
		if(where[col] != -1)
			answer[col] = divide(a[where[col]][m], a[where[col]][col]);
	for(int row = 0; row < n; ++row) {
		T got = 0;
		for(int col = 0; col < m; ++col)
			got = add(got, mul(answer[col], a[row][col]));
		if(not equal(got, a[row][m]))
			return {0, answer};
	}
	for(int col = 0; col < m; ++col)
		if(where[col] == -1)
			return {2, answer};
	return {1, answer};
}
