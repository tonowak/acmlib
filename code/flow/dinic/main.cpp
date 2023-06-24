/*
 * Opis: Dinic bez skalowania
 * Czas: O(V^2 E)
 * Użycie: Dinic flow(2); flow.add_edge(0, 1, 5); cout << flow(0, 1); // 5
 *   funkcja get_flowing() zwraca dla każdej oryginalnej krawędzi, ile przez nią leci
 */

struct Dinic {
	using T = int;
	struct Edge {
		int v, u;
		T flow, cap;
	};
	int n;
	vector<vector<int>> graph;
	vector<Edge> edges;

	Dinic(int N) : n(N), graph(n) {}

	void add_edge(int v, int u, T cap) {
		debug(v, u, cap);
		int e = ssize(edges);
		graph[v].emplace_back(e);
		graph[u].emplace_back(e + 1);
		edges.emplace_back(Edge{v, u, 0, cap});
		edges.emplace_back(Edge{u, v, 0, 0});
	}

	vector<int> dist;
	bool bfs(int source, int sink) {
		dist.assign(n, 0);
		dist[source] = 1;
		deque<int> que = {source};
		while(ssize(que) and dist[sink] == 0) {
			int v = que.front();
			que.pop_front();
			for(int e : graph[v])
				if(edges[e].flow != edges[e].cap and dist[edges[e].u] == 0) {
					dist[edges[e].u] = dist[v] + 1;
					que.emplace_back(edges[e].u);
				}
		}
		return dist[sink] != 0;
	}

	vector<int> ended_at;
	T dfs(int v, int sink, T flow = numeric_limits<T>::max()) {
		if(flow == 0 or v == sink)
			return flow;
		for(; ended_at[v] != ssize(graph[v]); ++ended_at[v]) {
			Edge &e = edges[graph[v][ended_at[v]]];
			if(dist[v] + 1 == dist[e.u])
				if(T pushed = dfs(e.u, sink, min(flow, e.cap - e.flow))) {
					e.flow += pushed;
					edges[graph[v][ended_at[v]] ^ 1].flow -= pushed;
					return pushed;
				}
		}
		return 0;
	}

	T operator()(int source, int sink) {
		T answer = 0;
		while(bfs(source, sink)) {
			ended_at.assign(n, 0);
			while(T pushed = dfs(source, sink))
				answer += pushed;
		}
		return answer;
	}

	map<pair<int, int>, T> get_flowing() {
		map<pair<int, int>, T> ret;
		REP(v, n)
			for(int i : graph[v]) {
				if(i % 2) // considering only original edges
					continue;
				Edge &e = edges[i];
				ret[pair(v, e.u)] += e.flow;
			}
		return ret;
	}
};
