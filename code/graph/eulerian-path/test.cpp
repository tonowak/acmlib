#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<PII>> graph(n);
	REP(i, m) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].emplace_back(b - 1, i);
		graph[b - 1].emplace_back(a - 1, i);
	}
	debug(EulerianPath(m, graph).path);
}
