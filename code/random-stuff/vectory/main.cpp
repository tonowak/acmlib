/*
 * Opis: Funcja tworząca wielowymierowe vectory, wymaga C++17
 * Użycie: create(a, b, c, d, def) stworzy czterowymiarowy vector gdzie domyślna wartość to def
 * auto dp = create(n, n, n, -1);
 */

template<class T> auto create(T x) { return x; }
template<class... Ts> auto create(int n, Ts... x) {
	return vector(n, create(x...));
}
