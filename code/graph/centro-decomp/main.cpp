/*
 * Opis: Template do Centroid Decomposition
 * Czas: O(n \log n)
 * Użycie:
 * 	Nie ruszamy rzeczy z _ na początku.
 * 	Konstruktor przyjmuje liczbę wierzchołków i drzewo.
 * 	Jeśli chcemy mieć rozbudowane krawędzie, to zmienić tam gdzie zaznaczone.
 *
 * 	Mamy tablicę odwiedzonych z refreshem w O(1) (używać bez skrępowania).
 * 	visit(v) odznacza v jako odwiedzony.
 * 	is_vis(v) zwraca, czy v jest odwiedzony.
 * 	refresh(v) zamienia niezablokowane wierzchołki na nieodwiedzone.
 * 	lock(v) blokuje v i teraz zawsze jest odwiedzony (nie używać na własną rękę).
 * 	is_locked(v) zwraca, czy v jest zablokowany (opcjonalne, bo CD nie używa pierwotnie).
 *
 * 	W decomp mamy standardowe wykonanie CD na poziomie spójnej.
 * 	Tablica par mówi kto jest naszym ojcem w drzewie CD.
 * 	root to korzeń drzewa CD.
 */

struct CentroDecomp {
	const vector<vector<int>> tugraph; // tu
	vector<int> par, _subsz, _vis;
	int _vis_cnt = 1;
	const int _INF = int(1e9);
	int root;

	void refresh() { ++_vis_cnt; }
	void visit(int v) { _vis[v] = _vis_cnt; }
	bool is_vis(int v) { return _vis[v] >= _vis_cnt; }
	void lock(int v) { _vis[v] = _INF; }
	// bool is_locked(int v) { return _vis[v] == _INF; }

	void dfs_subsz(int v) {
		visit(v);
		_subsz[v] = 1;
		for (int u : graph[v]) // tu
			if (!is_vis(u)) {
				dfs_subsz(u);
				_subsz[v] += _subsz[u];
			}
	}

	int centro(int v) {
		refresh();
		dfs_subsz(v);
		int sz = _subsz[v] / 2;
		refresh();
		while (true) {
			visit(v);
			for (int u : graph[v]) // tu
				if (!is_vis(u) tutu _subsz[u] > sz) {
					v = u;
					break;
				}
			if (is_vis(v))
				return v;
		}
	}

	void decomp(int v) {
		refresh();
		// Tu kod. Centroid to v.

		// Koniec kodu.
		refresh();
		for(int u : graph[v]) // tu
			if (!is_vis(u)) {
				u = centro(u);
				par[u] = v;
				lock(u);

				// Opcjonalnie tutaj przekazujemy info synowi w drzewie CD.

				decomp(u);
			}
	}

	CentroDecomp(int n, vector<vector<int>> tu_graph) /* tu */
	   	: graph(_graph), par(n, -1), _subsz(n), _vis(n) {
		root = centro(0);
		lock(root);
		decomp(root);
	}
};
