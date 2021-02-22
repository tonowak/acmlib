#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

struct Test {
	vector<vector<int>> graph;
	vector<LL> sums;
	HLD hld;

	Test(int n, vector<vector<int>> _graph) : graph(_graph), sums(n), hld(n, graph) {}

	void add(int v, int u, LL val) {
		auto path = hld.get_path(v, u);
		for(auto &p : path) {
			assert(p.first <= p.second);
			for(int j = p.first; j <= p.second; j++)
				sums[j] += val;
		}
	}

	LL query(int v, int u) {
		 LL ret = 0;
		 auto path = hld.get_path(v, u);
		 for(auto &p : path) {
			assert(p.first <= p.second);
			for(int j = p.first; j <= p.second; j++)
				ret += sums[j];
		 }
		 return ret;
	}
};

struct Brute {
	vector<vector<int>> graph;
	vector<LL> sums;

	bool found;
	LL dfs(int v, int u, LL val, int p = -1) {
		if(p == -1) found = false;
		if(v == u) {
			found = true;
			sums[v] += val;
			return sums[v];
		}

		for(int x : graph[v]) if(x != p) {
			LL ret = dfs(x, u, val, v);
			if(found) {
				sums[v] += val;
				return ret + sums[v];
			}
		}

		return 0;
	}

	void add(int v, int u, LL val) {
		dfs(v, u, val);	
	}

	LL query(int v, int u) {
		return dfs(v, u, 0);	
	}

	Brute(int n, vector<vector<int>> _graph) : graph(_graph), sums(n) {}
};

void test() {
	int N = 100;
	int n = rd(1, N);
	int q = rd(1, N);

	vector<vector<int>> graph(n);
	REP(i, n - 1) {
		int v = i + 1;
		int p = rd(0, v - 1);
		graph[v].emplace_back(p);
		graph[p].emplace_back(v);
	}

	Test hld(n, graph);	
	Brute brut(n, graph);

	REP(i, q)
		if(rd(0, 1)) {
			int v = rd(0, n - 1), u = rd(0, n - 1), val = rd(1, 100);
			hld.add(v, u, val);
			brut.add(v, u, val);
		}
		else {
			int v = rd(0, n - 1), u = rd(0, n - 1);
			assert(hld.query(v, u) == brut.query(v, u));
		}
}	
