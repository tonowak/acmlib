/*
 * Opis: O(n \log n), zwraca wszystkie skompresowane trójki
 * $(start\_l, start\_r, len)$ oznaczające, że podsłowa zaczynające się w
 * $[start\_l, start\_r]$ o długości $len$ są kwadratami,
 * jest ich O(n \log n).
 */
#include "../pref/main.cpp"

vector<tuple<int, int, int>> squares(const vector<int> &s) {
	vector<tuple<int, int, int>> ans;
	vector pos(ssize(s) / 2 + 2, -1);
	FOR(mid, 1, ssize(s) - 1) {
		int part = mid & ~(mid - 1), off = mid - part;
		int end = min(mid + part, ssize(s));
		vector a(s.begin() + off, s.begin() + off + part),
			b(s.begin() + mid, s.begin() + end),
			ra(a.rbegin(), a.rend());
		REP(j, 2) {
			 auto z1 = pref(ra), bha = b;
			 bha.emplace_back(-1);
			 for(int x : a) bha.emplace_back(x);
			 auto z2 = pref(bha);
			 for(auto *v : {&z1, &z2}) {
				 v[0][0] = ssize(v[0]);
				 v->emplace_back(0);
			 }
			 REP(c, ssize(a)) {
				int l = ssize(a) - c, x = c - min(l - 1, z1[l]),
					y = c - max(l - z2[ssize(b) + c + 1], j),
					sb = (j ? end - y - l * 2 : off + x),
					se = (j ? end - x - l * 2 + 1 : off + y + 1),
					&p = pos[l];
				if (x > y) continue;
				if (p != -1 && get<1>(ans[p]) + 1 == sb)
					get<1>(ans[p]) = se - 1;
				else
					p = ssize(ans), ans.emplace_back(sb, se - 1, l);
			 }
			 a = vector(b.rbegin(), b.rend());
			 b.swap(ra);
		 }
	}
	return ans;
}
