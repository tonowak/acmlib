/*
 * Opis: O(n \log n), template do Centroid Decomposition
 * 	Nie ruszamy rzeczy z \_ na początku.
 * 	Konstruktor przyjmuje liczbę wierzchołków i drzewo.
 * 	Jeśli chcemy mieć rozbudowane krawędzie, to zmienić tam gdzie zaznaczone.
 * 	Mamy tablicę odwiedzonych z refreshem w O(1) (używać bez skrępowania).
 * 	\texttt{visit(v)} odznacza v jako odwiedzony.
 * 	\texttt{is\_vis(v)} zwraca, czy v jest odwiedzony.
 * 	\texttt{refresh(v)} zamienia niezablokowane wierzchołki na nieodwiedzone.
 * 	W decomp mamy standardowe wykonanie CD na poziomie spójnej.
 * 	Tablica \texttt{par} mówi kto jest naszym ojcem w drzewie CD.
 * 	\texttt{root} to korzeń drzewa CD.
 */
struct CentroDecomp {
	const vector<vector<int>> &graph; // tu
	vector<int> par, subsz, vis;
	int vis_cnt = 1;
	const int INF = int(1e9);
	int root;
	void refresh() { ++vis_cnt; }
	void visit(int v) { vis[v] = max(vis[v], vis_cnt); }
	bool is_vis(int v) { return vis[v] >= vis_cnt; }
	void dfs_subsz(int v) {
		visit(v);
		subsz[v] = 1;
		for (int u : graph[v]) // tu
			if (!is_vis(u)) {
				dfs_subsz(u);
				subsz[v] += subsz[u];
			}
	}
	int centro(int v) {
		refresh();
		dfs_subsz(v);
		int sz = subsz[v] / 2;
		refresh();
		while (true) {
			visit(v);
			for (int u : graph[v]) // tu
				if (!is_vis(u) && subsz[u] > sz) {
					v = u;
					break;
				}
			if (is_vis(v))
				return v;
		}
	}
	void decomp(int v) {
		refresh();
		// Tu kod. Centroid to v, ktory jest juz dozywotnie odwiedzony.
		// Koniec kodu.
		refresh();
		for(int u : graph[v]) // tu
			if (!is_vis(u)) {
				u = centro(u);
				par[u] = v;
				vis[u] = INF;
				// Opcjonalnie tutaj przekazujemy info synowi w drzewie CD.
				decomp(u);
			}
	}
	CentroDecomp(int n, vector<vector<int>> &grph) // tu
	   	: graph(grph), par(n, -1), subsz(n), vis(n) {
		root = centro(0);
		vis[root] = INF;
		decomp(root);
	}
};
