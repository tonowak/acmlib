/*
 * Opis: dla $S$ wyznacza minimalny zbiór $B$, że każdy element $S$ można zapisać jako xor jakiegoś podzbioru $B$.
 * Czas: O(nB + B^2) dla $B=bits$
 */

constexpr int bits = 30;
vector<int> xor_base(vector<int> elems) {
	vector<vector<int>> at_bit(bits);
	for(int ai : elems)
		at_bit[highest_bit(ai)].emplace_back(ai);

	for(int b = bits - 1; b >= 0; --b)
		while(ssize(at_bit[b]) > 1) {
			int ai = at_bit[b].back();
			at_bit[b].pop_back();
			a ^= at_bit[b].back();
			at_bit[highest_bit(ai)].emplace_back(ai);
		}

	FOR(b0, 1, bits - 1)
		for(int a0 : at_bit[b0])
			FOR(b1, b0 + 1, bits - 1)
				for(int &a1 : at_bit[b1])
					if((a1 >> b0) & 1)
						a1 ^= a0;

	vector<int> ret;
	for(auto &v : at_bit)
		for(int ai : v)
			ret.emplace_back(ai);
	return ret;
}
