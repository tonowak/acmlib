/*
 * Opis: O(V E + |flow| E \log V), Min-cost max-flow.
 *   Można przepisać funkcję get\_flowing() z Dinic'a.
 *   Kiedy wie się coś więcej o początkowym grafie np. że jest DAG-iem lub że ma tylko nieujemne wagi krawędzi, można napisać własne calc\_init\_dist by usunąć $V E$ ze złożoności.
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
	vector<LL> init_dist;
	MCMF(int N) : n(N), graph(n), init_dist(n) {}
	void add_edge(int v, int u, int cap, LL cost) {
		int e = ssize(edges);
		graph[v].emplace_back(e);
		graph[u].emplace_back(e + 1);
		edges.emplace_back(v, u, 0, cap, cost);
		edges.emplace_back(u, v, 0, 0, -cost);
	}
	void calc_init_dist(int source) {
		fill(init_dist.begin(), init_dist.end(), inf_LL);
		vector<bool> inside(n);
		inside[source] = true;
		deque<int> que = {source};
		init_dist[source] = 0;
		while (ssize(que)) {
			int v = que.front();
			que.pop_front();
			inside[v] = false;
			for (int i : graph[v]) {
				Edge &e = edges[i];
				if (e.flow < e.cap and init_dist[v] + e.cost < init_dist[e.u]) {
					init_dist[e.u] = init_dist[v] + e.cost;
					if (not inside[e.u]) {
						inside[e.u] = true;
						que.emplace_back(e.u);
					}
				}
			}
		}
	}
	pair<int, LL> augment(int source, int sink) {
		vector<bool> vis(n);
		vector<int> from(n, -1);
		vector<LL> dist(n, inf_LL);
		priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<>> que;
		que.emplace(0, source);
		dist[source] = 0;
		while(ssize(que)) {
			auto [d, v] = que.top();
			que.pop();
			if (vis[v]) continue;
			vis[v] = true;
			for (int i : graph[v]) {
				Edge &e = edges[i];
				LL new_dist = d + e.cost + init_dist[v];
				if (not vis[e.u] and e.flow != e.cap and new_dist < dist[e.u]) {
					dist[e.u] = new_dist;
					from[e.u] = i;
					que.emplace(new_dist - init_dist[e.u], e.u);
				}
			}
		}
		if (not vis[sink])
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
		init_dist.swap(dist);
		return {flow, flow * init_dist[sink]};
	}
	pair<int, LL> operator()(int source, int sink) {
		calc_init_dist(source);
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
