
/*
 * Opis: Dwuspójne składowe
 * Czas: O(n)
 * Użycie: add_edge(u, v) dodaje krawędź (u, v), u != v, bo get() nie działa
 * po wywołaniu init() w .bicon mamy dwuspójne(vector ideków krawędzi na każdą), w .edges mamy krawędzie
 */

struct BiconComps {
	using PII = pair<int, int>;
	vector<vector<int>> graph, bicon;
	vector<int> low, pre, s;
	vector<array<int, 2>> edges;
	BiconComps(int n) : graph(n), low(n), pre(n, -1) {}
	void add_edge(int u, int v) {
		int q = ssize(edges);
		graph[u].emplace_back(q);
		graph[v].emplace_back(q);
		edges.push_back({u, v});
	}
	int get(int v, int id) {
		for(int r : edges[id])
			if(r != v) return r;
	}
	int t = 0;
	void dfs(int v, int p) {
		low[v] = pre[v] = t++;
		bool par = false;
		for(int e : graph[v]) {
			int u = get(v, e);
			if(u == p && !par) {
				par = true;
				continue;
			}
			else if(pre[u] == -1) {
				s.emplace_back(e); dfs(u, v);
				low[v] = min(low[v], low[u]);
				if(low[u] >= pre[v]) {
					bicon.emplace_back();
					do {
						bicon.back().emplace_back(s.back());
						s.pop_back();
					} while(bicon.back().back() != e);
				}
			}
			else if(pre[v] > pre[u]) {
				low[v] = min(low[v], pre[u]);
				s.emplace_back(e);
			}
		}
	}
	void init() { dfs(0, -1); }
};
