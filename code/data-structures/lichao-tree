// todo: dodać komentarze, używać headerów, dodać test.cpp

struct Function {
	int a, b;

	L operator()(int x) {
		return x * L(a) + b;
	}

	Function(int p = 0, int q = inf) : a(p), b(q) {}
};

ostream& operator<<(ostream &os, Function f) {
	return os << '(' << f.a << ", " << f.b << ')';
}

struct LiChaoTree {
	int size = 1;
	vector<Function> tree;

	LiChaoTree(int n) {
		while(size < n)
			size <<= 1;
		tree.resize(size << 1);
	}

	L get_min(int x) {
		int v = x + size;
		L ans = inf;
		while(v) {
			ans = min(ans, tree[v](x));
			v >>= 1;
		}
		return ans;
	}

	void add_func(Function new_func, int v, int l, int r) {
		int m = (l + r) / 2;
		bool domin_l = tree[v](l) > new_func(l),
			 domin_m = tree[v](m) > new_func(m);
		if(domin_m)
			swap(tree[v], new_func);

		if(l == r)
			return;
		else if(domin_l == domin_m)
			add_func(new_func, v << 1 | 1, m + 1, r);
		else
			add_func(new_func, v << 1, l, m);
	}

	void add_func(Function new_func) {
		add_func(new_func, 1, 0, size - 1);
	}
};
	

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int mx, q;
	cin >> mx >> q;
	LiChaoTree tree(mx + 1);

	while(q --> 0) {
		char c;
		cin >> c;
		if(c == 'A') {
			int a, b;
			cin >> a >> b;
			tree.add_func(Function{a, b});
		} else {
			int x;
			cin >> x;
			cout << tree.get_min(x) << nl;
		}

		D << I(tree.tree);
	}
}
