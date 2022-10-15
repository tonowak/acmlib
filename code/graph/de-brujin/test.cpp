#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	bool is_path = rd(0, 1);
	const int max_n = 5;
	const int max_k = 6;
	int n = rd(1, max_n);
	int k = rd(1, max_k);
	auto path = de_brujin(k, n, is_path);
	debug(n, k, is_path, path);
	map<vector<int>, int> m;
	int N = 1;
	REP(i, n)
		N *= k;
	if (is_path) {
		const int length = k > 1 ? N + n - 1 : n;
		assert(ssize(path) == length);
		REP(i, N) {
			vector<int> v(path.begin() + i, path.begin() + i + n);
			++m[v];
		}
	}
	else {
		const int length = k > 1 ? N : n;
		assert(ssize(path) == length);
		REP(i, N) {
			vector<int> v(path.begin(), path.begin() + n);
			++m[v];
			rotate(path.begin(), path.begin() + 1, path.end());
		}
	}
	debug(m);
	for (auto [a, b] : m) {
		for (auto e : a)
			assert(0 <= e and e < k);
		assert(b == 1);
	}
}
