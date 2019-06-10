#include<bits/stdc++.h>
using namespace std;

#define REP(i, a) for(int i = 0; i < a; i++)
#define ST first
#define ND second

using LL = long long;

#include "main.cpp"

struct test
{
	vector<vector<int>> graph;
	vector<LL> sums;
	HLD hld;

	test(int n, vector<vector<int>> graph) : graph(graph), hld(n, graph), sums(n) {}

	void add(int v, int u, LL val)
	{
		auto path = hld.get_path(v, u);
		for(auto &p : path)
		{
			assert(p.ST <= p.ND);
			for(int j = p.ST; j <= p.ND; j++)
				sums[j] += val;
		}
	}

	LL query(int v, int u)
	{
		 LL ret = 0;
		 auto path = hld.get_path(v, u);
		 for(auto &p : path)
		 {
			assert(p.ST <= p.ND);
			for(int j = p.ST; j <= p.ND; j++)
				ret += sums[j];
		 }
		 return ret;
	}
};

struct brute
{
	vector<vector<int>> graph;
	vector<LL> sums;

	bool found;
	LL dfs(int v, int u, LL val, int p = -1)
	{
		if(p == -1) found = false;
		if(v == u)
		{
			found = true;
			sums[v] += val;
			return sums[v];
		}

		for(int x : graph[v]) if(x != p)
		{
			LL ret = dfs(x, u, val, v);
			if(found)
			{
				sums[v] += val;
				return ret + sums[v];
			}
		}

		return 0;
	}

	void add(int v, int u, LL val)
	{
		dfs(v, u, val);	
	}

	LL query(int v, int u)
	{
		return dfs(v, u, 0);	
	}

	brute(int n, vector<vector<int>> graph) : graph(graph), sums(n) {}
};

mt19937 _gen(chrono::system_clock::now().time_since_epoch().count());
int rd(int a, int b) { return uniform_int_distribution<int>(a, b)(_gen); }

int main()
{
	ios_base::sync_with_stdio(0);
 	cin.tie(0);

	int N = 2000;
	auto get_time = [&]() { return chrono::system_clock::now().time_since_epoch().count(); };
	auto start = get_time();
	int seconds = 5;

	while(get_time() - start < 1e9 * seconds)
	{
		int n = rd(1, N);
		int q = rd(1, N);

		vector<vector<int>> graph(n);
		REP(i, n - 1)
		{
			int v = i + 1;
			int p = rd(0, v - 1);
			graph[v].emplace_back(p);
			graph[p].emplace_back(v);
		}

		test hld(n, graph);	
		brute brut(n, graph);

		REP(i, q)
		{
			if(rd(0, 1))
			{
				int v = rd(0, n - 1), u = rd(0, n - 1), val = rd(1, 100);
				hld.add(v, u, val);
				brut.add(v, u, val);
			}
			else
			{
				int v = rd(0, n - 1), u = rd(0, n - 1);
				assert(hld.query(v, u) == brut.query(v, u));
			}
		}
	}

	cout << "OK\n";
}	
