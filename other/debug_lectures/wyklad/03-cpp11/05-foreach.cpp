#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<int> vec = { 1, 2, 9 };
	for(int &x : vec)
		x *= 2;
	for(int x : vec)
		cout << x << ' ';
	cout << endl;
}

/////

vector<vector<int>> graph;
vector<bool> visited;

void DFS(int v) {
	cout << v << endl;
	visited[v] = true;
	for(int u : graph[v])
		DFS(u);
}
