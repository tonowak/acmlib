/*
 * Status: Przetestowane na zadankach
 * Opis: Find Union z mniejszy do wiekszego
 * Czas: O(\alpha(n)) oraz O(n) pamięciowo
 */

struct FindUnion {
	vector<int> rep;
	int size(int x) { return -rep[find(x)]; }
	int find(int x) {
		return rep[x] < 0 ? x : rep[x] = find(rep[x]);
	}
	bool same_set(int a, int b) { return find(a) == find(b); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b)
			return false;
		if(-rep[a] < -rep[b])
			swap(a, b);
		rep[a] += rep[b];
		rep[b] = a;
		return true;
	}
	FindUnion(int n) : rep(n, -1) {}
};

