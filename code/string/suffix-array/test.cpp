#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str;
	cin >> str;
	SuffixArray q(str);
	debug(q.sa);
	debug(q.lcp);
}
