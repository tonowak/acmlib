/*
 * Opis: Drzewo przedział-przedział
 * Czas: O(\log n)
 * Pamięć : O(n)
 * Użycie:
 *   add(l, r, val) dodaje na przedziale
 *   quert(l, r) bierze maxa z przedziału
 *   Zmieniając z maxa na co innego trzeba edytować
 *   funkcje add_val i f
 */

using T = int;
struct Node {
	T val, lazy;
	int size = 1;
};

struct Tree {
	vector<Node> nodes;
	int size = 1;

	void add_val(int v, T val) {
		nodes[v].val += val;
		nodes[v].lazy += val;
	}

	T f(T a, T b) { return max(a, b); }

	Tree(int n) {
		while(size < n) size *= 2;
		nodes.resize(size * 2);
		for(int i = size - 1; i >= 1; i--)
			nodes[i].size = nodes[i * 2].size * 2;
	}

	void propagate(int v) {
		REP(i, 2)
			add_val(v * 2 + i, nodes[v].lazy);
		nodes[v].lazy = 0;
	}

	T query(int l, int r, int v = 1) {
		if(l == 0 && r == nodes[v].size - 1)
			return nodes[v].val;
		propagate(v);	
		int m = nodes[v].size / 2;
		if(r < m)
			return query(l, r, v * 2);
		else if(m <= l)
			return query(l - m, r - m, v * 2 + 1);
		else
			return f(query(l, m - 1, v * 2), query(0, r - m, v * 2 + 1));
	}

	void add(int l, int r, T val, int v = 1) {
		if(l == 0 && r == nodes[v].size - 1) {
			add_val(v, val);
			return;
		}
		propagate(v);
		int m = nodes[v].size / 2;
		if(r < m)
			add(l, r, val, v * 2);
		else if(m <= l)
			add(l - m, r - m, val, v * 2 + 1);
		else
			add(l, m - 1, val, v * 2), add(0, r - m, val, v * 2 + 1);

		nodes[v].val = f(nodes[v * 2].val, nodes[v * 2 + 1].val);
	}
};
