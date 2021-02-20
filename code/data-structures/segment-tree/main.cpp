/*
 * Opis: Drzewo punkt-przedział
 * Czas: O(\log n)
 * Pamięć : O(n)
 * Użycie:
 *   Tree(n, val = 0) tworzy drzewo o n liściach, o wartościach val
 *   update(pos, val) zmienia element pos na val
 *   query(l, r) zwraca f na przedziale
 *   edytujesz funkcję f, można T ustawić na long longa albo parę
 */

struct Tree {
	using T = int;
	T f(T a, T b) { return a + b; }
	vector<T> tree;
	int sz = 1;

	Tree(int n, T val = 0) {
		while(sz < n) sz *= 2;
		tree.resize(sz * 2, val);
	}

	void update(int pos, T val) {
		tree[pos += sz] = val;
		while(pos /= 2)
			tree[pos] = f(tree[pos * 2], tree[pos * 2 + 1]);
	}

	T query(int l, int r) {
		l += sz, r += sz;
		T ret = (l != r ? f(tree[l], tree[r]) : tree[l]);
		while(l + 1 < r) {
			if(l % 2 == 0)
				ret = f(ret, tree[l + 1]);
			if(r % 2 == 1)
				ret = f(ret, tree[r - 1]);
			l /= 2, r /= 2;
		}
		return ret;
	}
};
