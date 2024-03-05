/*
 * Opis: O(\log n) Implict Treap,
 *   wszystko indexowane od 0,
 *   do Node dopisujemy jakie chcemy mieć trzymać dodatkowo dane.
 *   Jeśli chcemy robić lazy, to wykonania push należy wstawić
 *   tam gdzie oznaczono komentarzem.
 */
namespace Treap {
	// BEGIN HASH
	mt19937 rng_key(0);
	struct Node {
		int prio, cnt = 1;
		Node *l = nullptr, *r = nullptr;
		Node() : prio(int(rng_key())) {}
		~Node() { delete l; delete r; }
	};
	using pNode = Node*;
	int get_cnt(pNode t) { return t ? t->cnt : 0; }
	void update(pNode t) {
		if (!t) return;
		// push(t);
		t->cnt = get_cnt(t->l) + get_cnt(t->r) + 1;
	}
	void split(pNode t, int i, pNode &l, pNode &r) {
		if (!t) {
			l = r = nullptr;
			return;
		}
		// push(t);
		if (i <= get_cnt(t->l))
			split(t->l, i, l, t->l), r = t;
		else
			split(t->r, i - get_cnt(t->l) - 1, t->r, r), l = t;
		update(t);
	}
	void merge(pNode &t, pNode l, pNode r) {
		if (!l or !r) t = l ?: r;
		else if (l->prio > r->prio) {
			// push(l);
			merge(l->r, l->r, r), t = l;
		}
		else {
			// push(r);
			merge(r->l, l, r->l), t = r;
		}
		update(t);
	} // END HASH
	void apply_on_interval(pNode &root, int l, int r, function<void (pNode)> f) {
		pNode left, mid, right;
		split(root, r + 1, mid, right);
		split(mid, l, left, mid);
		assert(l <= r and mid);
		f(mid);
		merge(mid, left, mid);
		merge(root, mid, right);
	}
}
