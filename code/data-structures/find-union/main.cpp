struct FindUnion {
	vector<int> rep;
	bool same_set(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -rep[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return;
		if(-rep[a] < -rep[b]) swap(a, b);
		rep[a] += rep[b];
		rep[b] = a;
	}
};
