/*
 * Opis: Zmajoryzowany set (według operacji większe)
 * Czas: O(\log n)
 * Użycie:
 * 	w cur jest zmajoryzowany set (cur)
 * 	insert(p) wrzuca parę p do setu, majoryzuje go (zamortyzowany czas)
 * 	i zwraca, czy podany element został dodany
 */

struct MajorizedSet {
	set<pair<int, int>> cur;

	MajorizedSet() {}

	bool insert(pair<int, int> p) {
		auto x = cur.lower_bound(p);
		if (x != cur.end() && (*x).second >= p.second)
			return false;
		while (true) {
			x = cur.upper_bound(p);
			if (x == cur.begin())
				break;
			--x;
			if ((*x).second <= p.second) {
				cur.erase(x);
				continue;
			}
			break;
		}
		cur.emplace(p);
		return true;
	}
};
