#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	if(n % 100 == 0)
		++n;
	cout << n;
}
