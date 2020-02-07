#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
int rd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

int main() {
	int max_n;
	cin >> max_n;
	cout << rd(1, max_n);
}
