/*
 * Opis: O(\log n),
 *   w \texttt{s} jest zmajoryzowany set,
 *   \texttt{insert(p)} wrzuca parę \texttt{p} do setu, majoryzuje go (zamortyzowany czas)
 *   i zwraca, czy podany element został dodany.
 */

template<typename A, typename B>
struct MajorizedSet {
	set<pair<A, B>> s;

	bool insert(pair<A, B> p) {
		auto x = s.lower_bound(p);
		if (x != s.end() && x->second >= p.second)
			return false;
		while (x != s.begin() && (--x)->second <= p.second)
			x = s.erase(x);
		s.emplace(p);
		return true;
	}
};
