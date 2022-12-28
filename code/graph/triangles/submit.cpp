#include "../../utils/main_test.cpp"
#include "main.cpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int T;
	cin >> T;
	while(T --> 0) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> graph(n);
		while(m --> 0) {
			int v, u;
			cin >> v >> u;
			--v, --u;
			graph[v].emplace_back(u);
			graph[u].emplace_back(v);
		}
		Triangles t(graph);
		__int128_t sum = t.ps4 + t.rectangles4 + t.paths4 + t.ys4 + t.stars4;
		constexpr int mod = int(1e9) + 7;
		cout << int(sum % mod) << '\n';
	}
}

