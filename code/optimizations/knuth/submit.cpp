#include "../../utils/main_test.cpp"
#include "main.cpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	while(cin >> n) {
		int m;
		cin >> m;
		vector<int> idx(m);
		for(int &i : idx)
			cin >> i;
		idx.emplace_back(n);
		++m;

		vector<vector<LL>> cost(m, vector<LL>(m));
		REP(l, m)
			FOR(r, l + 1, m - 1) {
				cost[l][r] = idx[r] - (l == 0 ? 0 : idx[l - 1]);
				debug(l, r, cost[l][r]);
			}
		cout << knuth_optimization(cost) << '\n';
	}
}
