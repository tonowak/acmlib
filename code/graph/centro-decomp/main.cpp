/*
 * Opis: template do Centroid Decomposition
 * Czas: O(n \log n)
 * Użycie:
 * 		a) traktujemy konstruktor jako main jeśli działanie wewnętrzne CD jest zbyt zależne od reszty kodu (potencjalnie wywalamy nawet przekazywanie grafu i każemy samemu wczytywać)
 * 		b) traktujemy jako blackbox z ograniczoną ilością informacji i wtedy dopisujemy kilka funkcji do rozwiązania jakiegoś prostego problemu na drzewie
 * 		konstruktor CentroDecomp(n, graf) - wywołuje dekompozycję
 * 		decomp(v) - wywołanie dla spójnej z centroidem v
 * 		root - korzeń drzewa centroidów
 * 		par - ojciec w drzewie centroidów (ojcem root jest -1)
 * Hinty:
 * 		- jeśli decomp i elementy związane z tą funkcją działają niepoprawnie (np. pętlą się), to najprawdopodobniej robimy coś nielegalnego z vis
 * 		- jeśli coś wylicza nam się niepoprawnie możliwe, że pomyliliśmy calle DFS -> w szczególność nie piszemy DFS, który wywołuje inny typ DFS
 * 		- jeśli chcemy optymalizować pamięć i rzeczy podobne, to można przepisać decomp aby działał jak BFS, a nie DFS
 */

struct CentroDecomp {
	using Neighbor = int;
	const vector<vector<Neighbor>> &graph;
	vector<int> par, _subsz, vis;
	int licz = 1;
	static constexpr int INF = int(1e9);
	int root;

	bool is_vis(int v) {
		return vis[v] >= licz;
	}

	void dfs_subsz(int v) {
		vis[v] = licz;
		_subsz[v] = 1;
		for (int u : graph[v])
			if (!is_vis(u)) {
				dfs_subsz(u);
				_subsz[v] += _subsz[u];
			}
	}

	int centro(int v) {
		++licz;
		dfs_subsz(v);
		int sz = _subsz[v] / 2;
		++licz;
		while (true) {
			vis[v] = licz;
			for (int u : graph[v])
				if (!is_vis(u) && _subsz[u] > sz) {
					v = u;
					break;
				}
			if (is_vis(v))
				return v;
		}
	}

	void decomp(int v) {
		// czynności na poziomie jednej spójnej z znanym centroidem v

		++licz;
		for(int u : graph[v])
			if (!is_vis(u)) {
				u = centro(u);
				par[u] = v;
				vis[u] = INF;

				// dodatkowe przekazanie informacji kolejnemu centroidowi np. jego głębokość

				decomp(u);
			}
	}

	CentroDecomp(int n, vector<vector<Neighbor>> &_graph) 
		: graph(_graph), par(n, -1), _subsz(n), vis(n) {
		root = centro(0);
		vis[root] = INF;
		decomp(root);
	}
};
