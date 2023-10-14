/* 
 * Opis: O(n \log n), \texttt{top\_bot\_hull} zwraca osobno górę i dół,
 *   \texttt{hull} zwraca punkty na otoczce clockwise gdzie pierwszy jest najbardziej lewym.
 */
#include "../point/main.cpp"
array<vector<P>, 2> top_bot_hull(vector<P> in) {
	sort(in.begin(), in.end());
	array<vector<P>, 2> ret;
	REP(d, 2) {
		for(auto p : in) {
			while(ssize(ret[d]) > 1 and dir(ret[d].end()[-2], ret[d].back(), p) >= 0)
				ret[d].pop_back();
			ret[d].emplace_back(p);
		}
		reverse(in.begin(), in.end());
	}
	return ret;
}
vector<P> hull(vector<P> in) {
	if(ssize(in) <= 2) return in;
	auto ret = top_bot_hull(in);
	REP(d, 2) ret[d].pop_back();
	ret[0].insert(ret[0].end(), ret[1].begin(), ret[1].end());
	return ret[0];
}
