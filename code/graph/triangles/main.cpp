/*
 * Opis: O(m \sqrt{m}), liczenie możliwych kształtów podzbiorów trzy- i czterokrawędziowych.
 * Suma zmiennych *3 daje liczbę spójnych 3-elementowych podzbiorów krawędzi, analogicznie suma zmiennych *4.
 */
struct Triangles {
	int triangles3 = 0;
	LL stars3 = 0, paths3 = 0;
	LL ps4 = 0, rectangles4 = 0, paths4 = 0;
	__int128_t ys4 = 0, stars4 = 0;
	Triangles(vector<vector<int>> &graph) {
		int n = ssize(graph);
		vector<pair<int, int>> sorted_deg(n);
		REP(i, n)
			sorted_deg[i] = {ssize(graph[i]), i};
		sort(sorted_deg.begin(), sorted_deg.end());
		vector<int> id(n);
		REP(i, n)
			id[sorted_deg[i].second] = i;
		vector<int> cnt(n);
		REP(v, n) {
			for(int u : graph[v]) if(id[v] > id[u])
				cnt[u] = 1;
			for(int u : graph[v]) if(id[v] > id[u]) for(int w : graph[u]) if(id[w] > id[u] and cnt[w]) {
				++triangles3;
				for(int x : {v, u, w})
					ps4 += ssize(graph[x]) - 2;
			}
			for(int u : graph[v]) if(id[v] > id[u])
				cnt[u] = 0;
			for(int u : graph[v]) if(id[v] > id[u]) for(int w : graph[u]) if(id[v] > id[w])
				rectangles4 += cnt[w]++;
			for(int u : graph[v]) if(id[v] > id[u]) for(int w : graph[u])
				cnt[w] = 0;
		}
		paths3 = -3 * triangles3;
		REP(v, n) for(int u : graph[v]) if(v < u)
			paths3 += (ssize(graph[v]) - 1) * LL(ssize(graph[u]) - 1);
		ys4 = -2 * ps4;
		auto choose2 = [&](int x) { return x * LL(x - 1) / 2; };
		REP(v, n) for(int u : graph[v])
			ys4 += (ssize(graph[v]) - 1) * choose2(ssize(graph[u]) - 1);
		paths4 = -(4 * rectangles4 + 2 * ps4 + 3 * triangles3);
		REP(v, n) {
			int x = 0;
			for(int u : graph[v]) {
				x += ssize(graph[u]) - 1;
				paths4 -= choose2(ssize(graph[u]) - 1);
			}
			paths4 += choose2(x);
		}
		REP(v, n) {
			int s = ssize(graph[v]);
			stars3 += s * LL(s - 1) * LL(s - 2);
			stars4 += s * LL(s - 1) * LL(s - 2) * LL(s - 3);
		}
		stars3 /= 6;
		stars4 /= 24;
	}
};
