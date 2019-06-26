/*
 * Opis: Michał popisz sie opisem
 * Użycie: todo
 */


struct Tree {
	using T = int;
	T f(T a, T b) { return a + b; }
	vector<T> nodes;
	int size = 1;

	Tree(int n, T val = 0) {
		while(size < n) size *= 2;
		nodes.resize(size * 2, val);
	}

	void update(int pos, T val) {
		nodes[pos += size] = val;
		while(pos /= 2)
			nodes[pos] = f(nodes[pos * 2], nodes[pos * 2 + 1]);
	}

	T query(int l, int r) {
		l += size, r += size;
		T ret = (l != r ? f(nodes[l], nodes[r]) : nodes[l]);
		while(l + 1 < r) {
			if(l % 2 == 0)
				ret = f(ret, nodes[l + 1]);
			if(r % 2 == 1)
				ret = f(ret, nodes[r - 1]);
			l /= 2, r /= 2;
		}
	}
};
