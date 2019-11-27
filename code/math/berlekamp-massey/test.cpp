#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main()
{
	int n;
	cin >> n;
	vector<int> x(n);
	REP(i, n) cin >> x[i];
	BerlekampMassey<int(1e9 + 696969)> bm(x);
	REP(k, 10) debug(k, bm.get(k));
}
