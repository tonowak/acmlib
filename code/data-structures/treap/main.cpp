/*
 * Opis: Implict Treap
 * Czas: wszystko w O(\log n)
 * Użycie:
 *   wszystko indexowane od 0
 *   insert(i, val) insertuję na pozycję i
 *   treap[i] zwraca i-tą wartość
 */

mt19937 rng_key(0);

struct Treap {
	struct Node {
		int prio, val, cnt;
		Node *l = nullptr, *r = nullptr;
		Node(int _val) : prio(int(rng_key())), val(_val) {}
		~Node() { delete l; delete r; }
	};
	using pNode = Node*;
	pNode root = nullptr;
	~Treap() { delete root; }

	int cnt(pNode t) { return t ? t->cnt : 0; }
	void update(pNode t) {
		if(!t) return;
		t->cnt = cnt(t->l) + cnt(t->r) + 1;
	}

	void split(pNode t, int i, pNode &l, pNode &r) {
		if(!t) l = r = nullptr;
		else if(i <= cnt(t->l))
			split(t->l, i, l, t->l), r = t;
		else
			split(t->r, i - cnt(t->l) - 1, t->r, r), l = t;
		update(t);
	}

	void merge(pNode &t, pNode l, pNode r) {
		if(!l || !r) t = (l ? l : r);
		else if(l->prio > r->prio)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
		update(t);
	}

	void insert(int i, int val) {
		pNode t;
		split(root, i, root, t);
		merge(root, root, new Node(val));
		merge(root, root, t);
	}
};
