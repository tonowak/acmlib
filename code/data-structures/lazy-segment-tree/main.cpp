/*
 * Opis: Drzewo przedział-przedział, w miarę abstrakcyjne. Wystarczy zmienić \texttt{Node} i funkcje na nim.
 */

struct Node {
	LL sum = 0, lazy = 0;
	int sz = 1;
};
void push_to_sons(Node &n, Node &l, Node &r) {
	auto push_to_son = [&](Node &c) {
		c.sum += n.lazy * c.sz;
		c.lazy += n.lazy;
	};
	push_to_son(l);
	push_to_son(r);
	n.lazy = 0;
}
Node merge(Node l, Node r) {
	return Node{
		.sum = l.sum + r.sum,
		.lazy = 0,
		.sz = l.sz + r.sz
	};
}
void add_to_base(Node &n, int val) {
	n.sum += n.sz * LL(val);
	n.lazy += val;
}

struct Tree {
	vector<Node> tree;
	int sz = 1;

	Tree(int n) {
		while(sz < n)
			sz *= 2;
		tree.resize(sz * 2);
		for(int v = sz - 1; v >= 1; v--)
			tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
	}

	void push(int v) {
		push_to_sons(tree[v], tree[2 * v], tree[2 * v + 1]);
	}
	Node get(int l, int r, int v = 1) {
		if(l == 0 and r == tree[v].sz - 1)
			return tree[v];
		push(v);
		int m = tree[v].sz / 2;
		if(r < m)
			return get(l, r, 2 * v);
		else if(m <= l)
			return get(l - m, r - m, 2 * v + 1);
		else
			return merge(get(l, m - 1, 2 * v), get(0, r - m, 2 * v + 1));
	}

	void update(int l, int r, int val, int v = 1) {
		if(l == 0 && r == tree[v].sz - 1) {
			add_to_base(tree[v], val);
			return;
		}
		push(v);
		int m = tree[v].sz / 2;
		if(r < m)
			update(l, r, val, 2 * v);
		else if(m <= l)
			update(l - m, r - m, val, 2 * v + 1);
		else {
			update(l, m - 1, val, 2 * v);
			update(0, r - m, val, 2 * v + 1);
		}
		tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
	}
};
