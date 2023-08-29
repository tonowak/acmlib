/*
 * Opis: Drzewa punkt-przedział. Pierwsze ustawia w punkcie i podaje max na przedziale. Drugie maxuje elementy na przedziale i podaje wartość w punkcie.
 */
struct Tree_Get_Max {
	using T = int;
	T f(T a, T b) { return max(a, b); }
	const T zero = 0;
	vector<T> tree;
	int sz = 1;
	Tree_Get_Max(int n) {
		while(sz < n)
			sz *= 2;
		tree.resize(sz * 2, zero);
	}
	void update(int pos, T val) {
		tree[pos += sz] = val;
		while(pos /= 2)
			tree[pos] = f(tree[pos * 2], tree[pos * 2 + 1]);
	}
	T get(int l, int r) {
		l += sz, r += sz;
		if(l == r)
			return tree[l];
		T ret_l = tree[l], ret_r = tree[r];
		while(l + 1 < r) {
			if(l % 2 == 0)
				ret_l = f(ret_l, tree[l + 1]);
			if(r % 2 == 1)
				ret_r = f(tree[r - 1], ret_r);
			l /= 2, r /= 2;
		}
		return f(ret_l, ret_r);
	}
};
struct Tree_Update_Max_On_Interval {
	using T = int;
	vector<T> tree;
	int sz = 1;
	Tree_Update_Max_On_Interval(int n) {
		while(sz < n)
			sz *= 2;
		tree.resize(sz * 2);
	}
	T get(int pos) {
		T ret = tree[pos += sz];
		while(pos /= 2)
			ret = max(ret, tree[pos]);
		return ret;
	}
	void update(int l, int r, T val) {
		l += sz, r += sz;
		tree[l] = max(tree[l], val);
		if(l == r)
			return;
		tree[r] = max(tree[r], val);
		while(l + 1 < r) {
			if(l % 2 == 0)
				tree[l + 1] = max(tree[l + 1], val);
			if(r % 2 == 1)
				tree[r - 1] = max(tree[r - 1], val);
			l /= 2, r /= 2;
		}
	}
};
