#include "../../utils/headers/main.cpp"
#include "main.cpp"

int main()
{
	int n;
	cin >> n;

	vector<LL> x(n);
	REP(i, n)
		cin >> x[i];

	auto rec = Berlekamp_Massey(x);
	debug(rec);

	LL k;
	cin >> k;
	cout << get_kth(x, rec, k);
}
