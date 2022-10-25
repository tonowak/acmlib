/*
 * Opis: Implict Treap
 * Czas: wszystko w O(\log n)
 * Użycie:
 *   wszystko indexowane od 0
 *   insert(key, val) insertuję na pozycję key
 *   treap[i] zwraca i-tą wartość
 */

mt19937 rng_key(0);	

struct Treap {
	struct Node {
		int prio, val, cnt;
		Node *l = nullptr, *r = nullptr;
		Node(int _val) : prio(rng_key()), val(_val) {}
	};
	using pNode = Node*;
	pNode root = nullptr;

	int cnt(pNode t) { return t ? t->cnt : 0; }
	void update(pNode t) {
		if(!t) return;
		t->cnt = cnt(t->l) + cnt(t->r) + 1;
	}

	void split(pNode t, int key, pNode &l, pNode &r) {
		if(!t) l = r = nullptr;
		else if(key <= cnt(t->l)) 
			split(t->l, key, l, t->l), r = t;
		else
			split(t->r, key - cnt(t->l) - 1, t->r, r), l = t;
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

	void insert(int key, int val) {
		pNode t;
		split(root, key, root, t);
		merge(root, root, new Node(val));
		merge(root, root, t);
	}
};
