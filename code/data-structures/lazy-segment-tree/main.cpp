// Drzewo Przedział Przedział
// Status : Nieprzetestowane
// add(l, r, val) dodaje na przedziale
// quert(l, r) bierze maxa z przedziału

struct Node {
	int val, lazy;
	int size = 1;
};

struct Tree {
	vector<Node> nodes;
	int size = 1;

	Tree(int n) {
		while(n < size) size *= 2;
		nodes.resize(size * 2);
		for(int i = size - 1; i >= 1; i--)
			nodes[i].size = nodes[i * 2].size * 2;
	}

	void propagate(int v)
	{
		nodes[v].val = max(nodes[v].val, nodes[v].lazy);
		nodes[v].lazy = 0;
		if(nodes[v].size == 1) return;
		REP(i, 2) nodes[v * 2 + i].lazu += nodes[v].lazy;
	}

	int query(int l, int r, int v = 1) {
		propagate(v);	
		if(l == 0 && r == nodes[v].size - 1)
			return nodes[v].val;
		int m = nodes[v].size / 2;
		if(r < m)
			return query(l, r, v * 2);
		else if(m <= l)
			return query(l - m, r - m, v * 2 + 1);
		else
			return max(query(l, m - 1, v * 2), query(0, r - m, v * 2 + 1));
	}

	void add(int l, int r, int val, int v = 1) {
		propagate(v);
		if(l == 0 && r == nodes[v].size - 1) {
			nodes[v].lazy += val;
			return;
		}
		int m = nodes[v].size / 2;
		if(r < m)
			add(l, r, val, v * 2);
		else if(m <= l)
			add(l - m, r - m, val, v * 2 + 1);
		else
			add(l, m - 1, val, v * 2), add(0, r - m, val, v * 2 + 1);
		nodes[v].val = max(nodes[v * 2].val, nodes[v * 2 + 1].val);
	}
};
