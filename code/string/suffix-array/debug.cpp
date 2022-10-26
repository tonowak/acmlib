#include "../../headers/main.cpp"
#include "main.cpp"

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str;
	cin >> str;
	vector<int> s(str.begin(), str.end());
	for(int &c : s)
		c -= 'a';
	SuffixArray q(s);
	debug(q.sa);
	debug(q.lcp);
}
