/*
 * Opis: Min-cost max-flow z SPFA
 * Czas: kto wie
 * Użycie: MCMF flow(2); flow.add_edge(0, 1, 5, 3); cout << flow(0, 1); // 15
 *   można przepisać funkcję get_flowing() z Dinic'a
 */

struct MCMF {
	struct Edge {
		int v, u, flow, cap;
		LL cost;
		friend ostream& operator<<(ostream &os, Edge &e) {
			return os << vector<LL>{e.v, e.u, e.flow, e.cap, e.cost};
		}
	};

	int n;
	const LL inf_LL = 1e18;
	const int inf_int = 1e9;
	vector<vector<int>> graph;
	vector<Edge> edges;

	MCMF(int N) : n(N), graph(n) {}

	void add_edge(int v, int u, int cap, LL cost) {
		int e = size(edges);
		graph[v].emplace_back(e);
		graph[u].emplace_back(e + 1);
		edges.emplace_back(Edge{v, u, 0, cap, cost});
		edges.emplace_back(Edge{u, v, 0, 0, -cost});
	}

	pair<int, LL> augment(int source, int sink) {
		vector<LL> dist(n, inf_LL);
		vector<int> from(n, -1);
		dist[source] = 0;
		deque<int> que = {source};
		vector<bool> inside(n);
		inside[source] = true;

		while(size(que)) {
			int v = que.front();
			inside[v] = false;
			que.pop_front();

			for(int i : graph[v]) {
				Edge &e = edges[i];
				if(e.flow != e.cap and dist[e.u] > dist[v] + e.cost) {
					dist[e.u] = dist[v] + e.cost;
					from[e.u] = i;
					if(not inside[e.u]) {
						inside[e.u] = true;
						que.emplace_back(e.u);
					}
				}
			}
		}
		if(from[sink] == -1)
			return {0, 0};

		int flow = inf_int, e = from[sink];
		while(e != -1) {
			flow = min(flow, edges[e].cap - edges[e].flow);
			e = from[edges[e].v];
		}
		e = from[sink];
		while(e != -1) {
			edges[e].flow += flow;
			edges[e ^ 1].flow -= flow;
			e = from[edges[e].v];
		}
		return {flow, flow * dist[sink]};
	}

	pair<int, LL> operator()(int source, int sink) {
		int flow = 0;
		LL cost = 0;
		pair<int, LL> got;
		do {
			got = augment(source, sink);
			flow += got.first;
			cost += got.second;
		} while(got.first);
		return {flow, cost};
	}
};
