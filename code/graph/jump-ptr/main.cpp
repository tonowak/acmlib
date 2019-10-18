/*
 * Opis: Jump Pointery
 * Czas: O(n \log n + q \log n)
 * Użycie:
 *   konstruktor - JumpPtr(graph)
 *   można ustawić roota
 *   jump_up(v, k) zwraca wierzchołek o k wyższy niż v
 *   jeśli nie istnieje, zwraca -1
 *   lca(a, b) zwraca lca wierzchołków
 */

struct JumpPtr {
	int LOG = 20;
	vector<vector<int>> graph, jump;
	vector<int> par, dep;

	void par_dfs(int v) {
		for(int u : graph[v]) {
			if(u != par[v]) {
				par[u] = v;
				dep[u] = dep[v] + 1;
				par_dfs(u);
			}
		}
	}
		
	JumpPtr(vector<vector<int>> &graph, int root = 0) : graph(graph) {
		int n = size(graph);
		par.resize(n, -1);
		dep.resize(n);
		par_dfs(root);
		
		jump.resize(LOG, vector<int>(n));
		jump[0] = par;
		FOR(i, 1, LOG - 1) REP(j, n)
			jump[i][j] = jump[i - 1][j] == -1 ? -1 : jump[i - 1][jump[i - 1][j]];
	}

	int jump_up(int v, int k) {
		for(int i = LOG - 1; i >= 0; i--)
			if(k & (1 << i))
				v = jump[i][v];
		return v;
	}

	int lca(int a, int b) {
		if(dep[a] < dep[b]) swap(a, b);
		int delta = dep[a] - dep[b];
		a = jump_up(a, delta);
		if(a == b) return a;
		
		for(int i = LOG - 1; i >= 0; i--) {
			if(jump[i][a] != jump[i][b]) {
				a = jump[i][a];
				b = jump[i][b];
			}
		}
		return par[a];		
	}
};
