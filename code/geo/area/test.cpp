#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main() { 
	int n;
	cin >> n;
	vector<P> pts(n);
	REP(i, n) cin >> pts[i];
	debug(area(pts));
}
