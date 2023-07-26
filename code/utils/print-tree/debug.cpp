#include "../headers/main.cpp"
#include "main.cpp"

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	REP(i, n - 1) {
		int a, b;
		cin >> a >> b;
		adj[a - 1].emplace_back(b - 1);
		adj[b - 1].emplace_back(a - 1);
	}

	print_tree(adj);
}

/*
input:
11
1 2
1 3
1 4
2 5
2 6
3 7
3 8
3 9
9 10
4 11

output:
0
├── 1
│   ├── 4
│   └── 5
├── 2
│   ├── 6
│   ├── 7
│   └── 8
│       └── 9
└── 3
    └── 10
 */
