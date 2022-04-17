/*
 * Opis: Drzewo potęgowe 2d offline
 * Czas: O(\log^2 n) Pamięć O(n \log n)
 * Użycie:
 * wywołujemy preprocess(x, y) na pozycjach, które chcemy updateować, później init()
 * update(x, y, val) dodaje val do a[x, y], query(x, y) zwraca sumę na prostokącie (0, 0) - (x, y)
 */
#include "../fenwick-tree/main.cpp"
struct Fenwick2d {
	vector<vector<int>> ys;
	vector<Fenwick> ft;
	Fenwick2d(int limx) : ys(limx) {}
	void preprocess(int x, int y) {
		for(; x < ssize(ys); x |= x + 1)
			ys[x].push_back(y);
	}
	void init() {
		for(auto &v : ys) {
			sort(v.begin(), v.end());
			ft.emplace_back(ssize(v) + 1);
		}
	}
	int ind(int x, int y) {
		auto it = lower_bound(ys[x].begin(), ys[x].end(), y);
		return distance(ys[x].begin(), it);
	}
	void update(int x, int y, LL val) {
		for(; x < ssize(ys); x |= x + 1)
			ft[x].update(ind(x, y), val);
	}
	LL query(int x, int y) {
		LL sum = 0;
		for(x++; x > 0; x &= x - 1)
			sum += ft[x - 1].query(ind(x - 1, y + 1) - 1);
		return sum;
	}
};
