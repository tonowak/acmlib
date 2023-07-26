/*
 * Opis: Funkcja do debugu która wypisuje ładnie drzewo, \texttt{print_tree(graph, root)}.
 */

#ifdef DEBUG
map<int, bool> edge;
void print_tree(vector<vector<int>> &graph, int v = 0, int p = -1, int dep = 0, bool end = false) {
	edge[dep] = true;
	REP(i, dep - 1) cerr << (edge[i] ? "│" : " ") << "   ";
	if(dep != 0) {
		if(end) edge[dep - 1] = false;
		cerr << (end ? "└" : "├") << "── ";
	}
	cerr << v << "\n";
	int last = -1;
	for(int u : graph[v]) if(u != p) last = u;
	for(int u : graph[v]) if(u != p)
		print_tree(graph, u, v, dep + 1, last == u);
	edge[dep] = false;
}
#else
#define print_tree(...) false
#endif

