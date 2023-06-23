/*
 * Opis: O(q \log n) Link-Cut Tree z wyznaczaniem odległości między wierzchołkami, lca w zakorzenionym drzewie, dodawaniem na ścieżce, dodawaniem na poddrzewie, zwracaniem sumy na ścieżce, zwracaniem sumy na poddrzewie.
 *   Przepisać co się chce (logika lazy jest tylko w \texttt{AdditionalInfo}, można np. zostawić puste funkcje).
 *   Wywołać konstruktor, potem \texttt{set\_value} na wierzchołkach (aby się ustawiło, że nie-nil to nie-nil) i potem jazda.
 */

struct AdditionalInfo {
	using T = LL;
	static constexpr T neutral = 0; // Remember that there is a nil vertex!
	T node_value = neutral, splay_value = neutral;//, splay_value_reversed = neutral;
	T whole_subtree_value = neutral, virtual_value = neutral;

	T splay_lazy = neutral; // lazy propagation on paths
	T splay_size = 0; // 0 because of nil
	T whole_subtree_lazy = neutral, whole_subtree_cancel = neutral; // lazy propagation on subtrees
	T whole_subtree_size = 0, virtual_size = 0; // 0 because of nil

	void set_value(T x) {
		node_value = splay_value = whole_subtree_value = x;
		splay_size = 1;
		whole_subtree_size = 1;
	}
	void update_from_sons(AdditionalInfo &l, AdditionalInfo &r) {
		splay_value = l.splay_value + node_value + r.splay_value;
		splay_size = l.splay_size + 1 + r.splay_size;
		whole_subtree_value = l.whole_subtree_value + node_value + virtual_value + r.whole_subtree_value;
		whole_subtree_size = l.whole_subtree_size + 1 + virtual_size + r.whole_subtree_size;
	}
	void change_virtual(AdditionalInfo &virtual_son, int delta) {
		assert(delta == -1 or delta == 1);
		virtual_value += delta * virtual_son.whole_subtree_value;
		whole_subtree_value += delta * virtual_son.whole_subtree_value;
		virtual_size += delta * virtual_son.whole_subtree_size;
		whole_subtree_size += delta * virtual_son.whole_subtree_size;
	}
	void push_lazy(AdditionalInfo &l, AdditionalInfo &r, bool /*reversed children*/) {
		l.add_lazy_in_path(splay_lazy);
		r.add_lazy_in_path(splay_lazy);
		splay_lazy = 0;
	}
	void cancel_subtree_lazy_from_parent(AdditionalInfo &parent) {
		whole_subtree_cancel = parent.whole_subtree_lazy;
	}
	void pull_lazy_from_parent(AdditionalInfo &parent) {
		if(splay_size == 0) // nil
			return;
		add_lazy_in_subtree(parent.whole_subtree_lazy - whole_subtree_cancel);
		cancel_subtree_lazy_from_parent(parent);
	}
	T get_path_sum() {
		return splay_value;
	}
	T get_subtree_sum() {
		return whole_subtree_value;
	}
	void add_lazy_in_path(T x) {
		splay_lazy += x;
		node_value += x;
		splay_value += x * splay_size;
		whole_subtree_value += x * splay_size;
	}
	void add_lazy_in_subtree(T x) {
		whole_subtree_lazy += x;
		node_value += x;
		splay_value += x * splay_size;
		whole_subtree_value += x * whole_subtree_size;
		virtual_value += x * virtual_size;
	}
};

struct Splay {
	struct Node {
		array<int, 2> child;
		int parent;
		int subsize_splay = 1;
		bool lazy_flip = false;

		AdditionalInfo info;
	};
	vector<Node> t;
	const int nil;

	Splay(int n) 
	: t(n + 1), nil(n) {
		t[nil].subsize_splay = 0;
		for(Node &v : t)
			v.child[0] = v.child[1] = v.parent = nil;
	}

	void apply_lazy_and_push(int v) {
		auto &[l, r] = t[v].child;
		if(t[v].lazy_flip) {
			for(int c : {l, r})
				t[c].lazy_flip ^= 1;
			swap(l, r);
		}
		t[v].info.push_lazy(t[l].info, t[r].info, t[v].lazy_flip);
		for(int c : {l, r})
			if(c != nil)
				t[c].info.pull_lazy_from_parent(t[v].info);
		t[v].lazy_flip = false;
	}

	void update_from_sons(int v) {
		// assumes that v's info is pushed
		auto [l, r] = t[v].child;
		t[v].subsize_splay = t[l].subsize_splay + 1 + t[r].subsize_splay;
		for(int c : {l, r})
			apply_lazy_and_push(c);
		t[v].info.update_from_sons(t[l].info, t[r].info);
	}

	// After that, v is pushed and updated
	void splay(int v) {
		apply_lazy_and_push(v);
		auto set_child = [&](int x, int c, int d) {
			if(x != nil and d != -1)
				t[x].child[d] = c;
			if(c != nil) {
				t[c].parent = x;
				t[c].info.cancel_subtree_lazy_from_parent(t[x].info);
			}
		};
		auto get_dir = [&](int x) -> int {
			int p = t[x].parent;
			if(p == nil or (x != t[p].child[0] and x != t[p].child[1]))
				return -1;
			return t[p].child[1] == x;
		};
		auto rotate = [&](int x, int d) {
			int p = t[x].parent, c = t[x].child[d];
			assert(c != nil);
			set_child(p, c, get_dir(x));
			set_child(x, t[c].child[!d], d);
			set_child(c, x, !d);
			update_from_sons(x);
			update_from_sons(c);
		};
		while(get_dir(v) != -1) {
			int p = t[v].parent, pp = t[p].parent;
			array path_up = {v, p, pp, t[pp].parent};
			for(int i = ssize(path_up) - 1; i >= 0; --i) {
				if(i < ssize(path_up) - 1)
					t[path_up[i]].info.pull_lazy_from_parent(t[path_up[i + 1]].info);
				apply_lazy_and_push(path_up[i]);
			}

			int dp = get_dir(v), dpp = get_dir(p);
			if(dpp == -1)
				rotate(p, dp);
			else if(dp == dpp) {
				rotate(pp, dpp);
				rotate(p, dp);
			}
			else {
				rotate(p, dp);
				rotate(pp, dpp);
			}
		}
	}
};

struct LinkCut : Splay {
	LinkCut(int n) : Splay(n) {}

	// Cuts the path from x downward, creates path to root, splays x.
	int access(int x) {
		int v = x, cv = nil;
		for(; v != nil; cv = v, v = t[v].parent) {
			splay(v);
			int &right = t[v].child[1];
			t[v].info.change_virtual(t[right].info, +1);
			right = cv;
			t[right].info.pull_lazy_from_parent(t[v].info);
			t[v].info.change_virtual(t[right].info, -1);
			update_from_sons(v);
		}
		splay(x);
		return cv;
	}

	// Changes the root to v.
	// Warning: Linking, cutting, getting the distance, etc, changes the root.
	void reroot(int v) {
		access(v);
		t[v].lazy_flip ^= 1;
		apply_lazy_and_push(v);
	}

	// Returns the root of tree containing v.
	int get_leader(int v) {
		access(v);
		while(apply_lazy_and_push(v), t[v].child[0] != nil)
			v = t[v].child[0];
		return v;
	}
	bool is_in_same_tree(int v, int u) {
		return get_leader(v) == get_leader(u);
	}

	// Assumes that v and u aren't in same tree and v != u.
	// Adds edge (v, u) to the forest.
	void link(int v, int u) {
		reroot(v);
		access(u);
		t[u].info.change_virtual(t[v].info, +1);
		assert(t[v].parent == nil);
		t[v].parent = u;
		t[v].info.cancel_subtree_lazy_from_parent(t[u].info);
	}

	// Assumes that v and u are in same tree and v != u.
	// Cuts edge going from v to the subtree where is u
	// (in particular, if there is an edge (v, u), it deletes it).
	// Returns the cut parent.
	int cut(int v, int u) {
		reroot(u);
		access(v);
		int c = t[v].child[0];
		assert(t[c].parent == v);
		t[v].child[0] = nil;
		t[c].parent = nil;
		t[c].info.cancel_subtree_lazy_from_parent(t[nil].info);
		update_from_sons(v);
		while(apply_lazy_and_push(c), t[c].child[1] != nil)
			c = t[c].child[1];
		return c;
	}

	// Assumes that v and u are in same tree.
	// Returns their LCA after a reroot operation.
	int lca(int root, int v, int u) {
		reroot(root);
		if(v == u) 
			return v;
		access(v);
		return access(u);
	}

	// Assumes that v and u are in same tree.
	// Returns their distance (in number of edges).
	int dist(int v, int u) {
		reroot(v);
		access(u);
		return t[t[u].child[0]].subsize_splay;
	}

	// Assumes that v and u are in same tree.
	// Returns the sum of values on the path from v to u.
	auto get_path_sum(int v, int u) {
		reroot(v);
		access(u);
		return t[u].info.get_path_sum();
	}

	// Assumes that v and u are in same tree.
	// Returns the sum of values on the subtree of v in which u isn't present.
	auto get_subtree_sum(int v, int u) {
		u = cut(v, u);
		auto ret = t[v].info.get_subtree_sum();
		link(v, u);
		return ret;
	}

	// Applies function f on vertex v (useful for a single add/set operation)
	void apply_on_vertex(int v, function<void (AdditionalInfo&)> f) {
		access(v);
		f(t[v].info);
		// apply_lazy_and_push(v); not needed
		// update_from_sons(v);
	}

	// Assumes that v and u are in same tree.
	// Adds val to each vertex in path from v to u.
	void add_on_path(int v, int u, int val) {
		reroot(v);
		access(u);
		t[u].info.add_lazy_in_path(val);
	}

	// Assumes that v and u are in same tree.
	// Adds val to each vertex in subtree of v that doesn't have u.
	void add_on_subtree(int v, int u, int val) {
		u = cut(v, u);
		t[v].info.add_lazy_in_subtree(val);
		link(v, u);
	}
};
