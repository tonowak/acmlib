/*
 * Status: Testowany ręcznie
 * Opis: Implict Persistent Treap
 * Czas: wszystko w O(\log n)
 * Użycie:
 *   wszystko indexowane od 0
 *   insert(key, val) insertuję na pozycję key
 *   kopiowanie struktury działa w O(1)
 *   robimy sobie vector<Treap>, żeby obsługiwać trwałość
 */

struct Treap {
	struct Node {
		int val, prio, sub = 1;
		Node *l = nullptr, *r = nullptr;
		Node(int val) : val(val), prio(rng()) {}
	};
	using pNode = Node*;
	pNode root = nullptr;

	int get_sub(pNode n) { return n ? n->sub : 0; }
	void update(pNode n) {
		if(!n) return;
		n->sub = get_sub(n->l) + get_sub(n->r) + 1;
	}

	void split(pNode t, int key, pNode &l, pNode &r) {
		if(!t) l = r = nullptr;
		else {
			t = new Node(*t);
			if(key <= get_sub(t->l))
				split(t->l, key, l, t->l), r = t;
			else
				split(t->r, key - get_sub(t->l) - 1, t->r, r), l = t;
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

	void insert(pNode &t, int key, pNode it) { 
		if(!t) t = it;
		else if(it->prio > t->prio)
			split(t, key, it->l, it->r), t = it;
		else {
			t = new Node(*t);
			if(key <= get_sub(t->l))
				insert(t->l, key, it);
			else
				insert(t->r, key - get_sub(t->l) - 1, it);
		}
		update(t);
	}
	void insert(int key, int val) {
		insert(root, key, new Node(val));
	}

	void erase(pNode &t, int key) {
		if(get_sub(t->l) == key)
			merge(t, t->l, t->r);
		else {
			t = new Node(*t);
			if(key <= get_sub(t->l))
				erase(t->l, key);
			else
				erase(t->r, key - get_sub(t->l) - 1);
		}
		update(t);
	}
	void erase(int key) {
		assert(key < get_sub(root));
		erase(root, key);
	}
};
