#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(0, 1) ? rd(1, 10) : rd(1, 100);
	int mx = rd(0, 1) ? 5 : int(1e9);
	vector<P> in(n);
	for(auto &p : in)
		while(true) {
			p = P(rd(-mx, mx), rd(-mx, mx));
			if(not equal(p, P(0, 0)))
				break;
		}
	in = angle_sort(in);

	vector<pair<int, int>> ret = angle180_intervals(in);
	assert(ssize(ret) == n);
	debug(ret);

	debug(in);
	REP(i, n) {
		set<int> good_indices;
		REP(j, n) {
			auto is_good = [&] {
				if(not equal(cross(in[i], in[j]), 0))
					return cross(in[i], in[j]) < 0;
				if(bool(P(0, 0) < in[i]) != bool(P(0, 0) < in[j]))
					return false;
				return i <= j;
			};
			if(is_good())
				good_indices.emplace(j);
		}
		debug(i, n, good_indices);

		int biggest_len = 0;
		while(biggest_len < n and good_indices.find((i + biggest_len) % n) != good_indices.end())
			++biggest_len;

		assert(ret[i].first == i);
		assert(ret[i].second == (i + biggest_len - 1) % n);
	}
}
