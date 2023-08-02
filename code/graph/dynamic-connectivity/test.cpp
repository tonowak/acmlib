#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

ostream& operator<<(ostream& o, tuple<auto,auto,auto> t) {
	return o << '(' << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ')';
}

void test() {
	int n = rd(1, 10);
	vector<tuple<int, int, Event_type>> events(rd(0, 20));
	for(auto &[v, u, t] : events) {
		v = rd(0, n - 1);
		u = rd(0, n - 1);
		t = Event_type(rd(0, 2));
	}
	debug(events);

	vector<multiset<int>> graph(n);
	vector<bool> brute;
	for(auto [v, u, t] : events)
		if(t == Query) {
			debug(graph);
			vector<bool> vis(n);
			function<void (int)> dfs = [&](int a) {
				vis[a] = true;
				for(int b : graph[a])
					if(not vis[b])
						dfs(b);
			};
			dfs(v);
			brute.emplace_back(vis[u]);
		}
		else if(t == Add) {
			graph[v].emplace(u);
			graph[u].emplace(v);
		}
		else
			for(int w : {v, u}) {
				int w2 = w ^ v ^ u;
				auto it = graph[w].find(w2);
				if(it != graph[w].end())
					graph[w].erase(it);
			}

	vector<bool> wzorc = dynamic_connectivity(n, events);
	debug(brute);
	debug(wzorc);
	assert(brute == wzorc);
}
