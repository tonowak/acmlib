/*
 * Opis: O(\log n) Implict Persistent Treap,
 *   wszystko indexowane od 0,
 *   \texttt{insert(i, val)} insertuję na pozycję $i$,
 *   kopiowanie struktury działa w O(1),
 *   robimy sobie \texttt{vector<Treap>} żeby obsługiwać trwałość
 */

mt19937 rng_i(0);

struct Treap {
	struct Node {
		int val, prio, sub = 1;
		Node *l = nullptr, *r = nullptr;
		Node(int _val) : val(_val), prio(int(rng_i())) {}
		~Node() { delete l; delete r; }
	};
	using pNode = Node*;
	pNode root = nullptr;

	int get_sub(pNode n) { return n ? n->sub : 0; }
	void update(pNode n) {
		if(!n) return;
		n->sub = get_sub(n->l) + get_sub(n->r) + 1;
	}

	void split(pNode t, int i, pNode &l, pNode &r) {
		if(!t) l = r = nullptr;
		else {
			t = new Node(*t);
			if(i <= get_sub(t->l))
				split(t->l, i, l, t->l), r = t;
			else
				split(t->r, i - get_sub(t->l) - 1, t->r, r), l = t;
		}
		update(t);
	}

	void merge(pNode &t, pNode l, pNode r) {
		if(!l || !r) t = (l ? l : r);
		else if(l->prio > r->prio) {
			l = new Node(*l);
			merge(l->r, l->r, r), t = l;
		}
		else {
			r = new Node(*r);
			merge(r->l, l, r->l), t = r;
		}
		update(t);
	}

	void insert(pNode &t, int i, pNode it) {
		if(!t) t = it;
		else if(it->prio > t->prio)
			split(t, i, it->l, it->r), t = it;
		else {
			t = new Node(*t);
			if(i <= get_sub(t->l))
				insert(t->l, i, it);
			else
				insert(t->r, i - get_sub(t->l) - 1, it);
		}
		update(t);
	}
	void insert(int i, int val) {
		insert(root, i, new Node(val));
	}

	void erase(pNode &t, int i) {
		if(get_sub(t->l) == i)
			merge(t, t->l, t->r);
		else {
			t = new Node(*t);
			if(i <= get_sub(t->l))
				erase(t->l, i);
			else
				erase(t->r, i - get_sub(t->l) - 1);
		}
		update(t);
	}
	void erase(int i) {
		assert(i < get_sub(root));
		erase(root, i);
	}
};
