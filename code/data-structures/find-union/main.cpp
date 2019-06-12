// status: untested
struct FindUnion {
	vector<int> rep;
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -rep[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return false;
		if(-rep[a] < -rep[b]) swap(a, b);
		rep[a] += rep[b];
		rep[b] = a;
		return true;
	}
	FindUnion(int n) : rep(n, -1) {}
};