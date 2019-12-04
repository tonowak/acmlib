/*
 * Opis: Dla pierwszego $p$ znajduje generator modulo $p$ 
 * Czas: O(\log^2(p)) (ale spora stała, zależy )
 */

#include "../rho-pollard/main.cpp"
LL exp(LL a, LL b, int m) {
	if(b == 0) return 1;
	if(b & 1) return a * exp(a, b - 1, m) % m;
	return exp(a * a % m, b / 2);
}
int primitive_root(int p) {
	int q = p - 1;
	vector<LL> v = factor(q); vector<int> fact;
	REP(i, v.size())
		if(!i or v[i] != v[i - 1]) 
			fact.emplace_back(v[i]);
	while(1) {
		int g = rd(2, q); bool good = 1;
		for(auto &f : fact)
			if(exp(g, q / f, p) == 1) {
				good = 0; break;
			}
		if(good) return g;
	}
}
