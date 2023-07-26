/*
 * Opis: O(\sqrt{m} \log n) czasowo, O(\sqrt{n}) pamięciowo,
 * dla liczby pierwszej $mod$ oraz $a, b \nmid mod$ znajdzie $e$ takie że $a^e \equiv b \pmod{mod}$. Jak zwróci $-1$ to nie istnieje.
*/

#include "../simple-modulo/main.cpp"

int discrete_log(int a, int b) {
	int n = int(sqrt(mod)) + 1;
	int an = 1;
	REP(i, n)
		an = mul(an, a);
	unordered_map<int, int> vals;
	int cur = b;
	FOR(q, 0, n) {
		vals[cur] = q;
		cur = mul(cur, a);
	}
	cur = 1;
	FOR(p, 1, n) {
		cur = mul(cur, an);
		if(vals.count(cur)) {
			int ans = n * p - vals[cur];
			return ans;
		}
	}
	return -1;
}
