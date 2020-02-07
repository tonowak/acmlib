#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main() { 
	int n;
	cin >> n;
	vector<P> pts(n);
	REP(i, n) cin >> pts[i];
	vector<int> top, bot;
	tie(top, bot) = top_bot_hull(pts);
	debug(top, bot);
}
