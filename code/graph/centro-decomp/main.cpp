/*
 * Opis: Template do Centroid Decomposition
 * Czas: O(n \log n)
 * Użycie:
 * 	Nie ruszamy rzeczy z _ na początku.
 * 	Konstruktor przyjmuje liczbę wierzchołków i drzewo.
 * 	Jeśli chcemy mieć rozbudowane krawędzie, to zmienić tam gdzie zaznaczone.
 * 	Mamy tablicę odwiedzonych z refreshem w O(1) (używać bez skrępowania).
 * 	visit(v) odznacza v jako odwiedzony.
 * 	is_vis(v) zwraca, czy v jest odwiedzony.
 * 	refresh(v) zamienia niezablokowane wierzchołki na nieodwiedzone.
 * 	W decomp mamy standardowe wykonanie CD na poziomie spójnej.
 * 	Tablica par mówi kto jest naszym ojcem w drzewie CD.
 * 	root to korzeń drzewa CD.
 */

struct CentroDecomp {
	const vector<vector<int>> &graph; // tu
	vector<int> par, _subsz, _vis;
	int _vis_cnt = 1;
	const int _INF = int(1e9);
	int root;

	void refresh() { ++_vis_cnt; }
	void visit(int v) { _vis[v] = max(_vis[v], _vis_cnt); }
	bool is_vis(int v) { return _vis[v] >= _vis_cnt; }

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
				if (!is_vis(u) && _subsz[u] > sz) {
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
				_vis[u] = _INF;

				// Opcjonalnie tutaj przekazujemy info synowi w drzewie CD.

				decomp(u);
			}
	}

	CentroDecomp(int n, vector<vector<int>> &_graph) // tu
	   	: graph(_graph), par(n, -1), _subsz(n), _vis(n) {
		root = centro(0);
		_vis[root] = _INF;
		decomp(root);
	}
};
