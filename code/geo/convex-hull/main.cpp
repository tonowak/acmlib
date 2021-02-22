/* 
 * Opis: Otoczka wypukła, osobno góra i dół
 * Czas: O(n \log n)
 * Użycie:
 * top_bot_hull zwraca osobno górę i dół po id
 * hull_id zwraca całą otoczkę po id
 * hull zwraca punkty na otoczce
 */
#include "../point/main.cpp"
Double cross(P a, P b, P c) { return sign(cross(b - a, c - a)); }
pair<vector<int>, vector<int>> top_bot_hull(vector<P> &pts) {
	int n = ssize(pts);
	vector<int> ord(n);
	REP(i, n) ord[i] = i;
	sort(ord.begin(), ord.end(), [&](int i, int j) {
		P &a = pts[i], &b = pts[j];
		return make_pair(a.x, a.y) < make_pair(b.x, b.y);
	});

	vector<int> top, bot;
	REP(dir, 2) {
		vector<int> &hull = (dir ? bot : top);
		auto l = [&](int i) { return pts[hull[ssize(hull) - i]]; };
		for(int i : ord) {
			while(ssize(hull) > 1 && cross(l(2), l(1), pts[i]) >= 0)
				hull.pop_back();
			hull.emplace_back(i);
		}
		reverse(ord.begin(), ord.end());
	}
	return {top, bot};
}

vector<int> hull_id(vector<P> &pts) {
	vector<int> top, bot;
	tie(top, bot) = top_bot_hull(pts);
	top.pop_back(), bot.pop_back();
	top.insert(top.end(), bot.begin(), bot.end());
	return top;
}

vector<P> hull(vector<P> &pts) {
	vector<P> ret;
	for(int i : hull_id(pts))
		ret.emplace_back(pts[i]);
	return ret;
}
