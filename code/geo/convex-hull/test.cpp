#include "../point/before_bits.cpp"
#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(0, 7);
	vector<P> in(n);
	for(auto &p : in)
		p = P(rd(-10, 10), rd(-10, 10));
	debug(in);

	vector<int> best_hull(n + 1);

	auto is_good_order = [&](vector<int> order) {
		if(ssize(order) <= 1)
			return ssize(order) == n;
		for(int i : order)
			if(in[i] < in[order[0]])
				return false;
		REP(i, ssize(order))
			REP(j, i)
				if(in[order[i]] == in[order[j]])
					return false;
		REP(i, ssize(order))
			for(int ord : order)
				if(dir(in[order[i]], in[order[(i + 1) % ssize(order)]], in[ord]) > 0)
					return false;
		REP(i, ssize(order))
			for(P p : in)
				if(dir(in[order[i]], in[order[(i + 1) % ssize(order)]], p) > 0)
					return false;
		return true;
	};

	vector<bool> taken(n);
	vector<int> curr_order;
	function<void ()> backtrack = [&] {
		if(is_good_order(curr_order) and ssize(curr_order) < ssize(best_hull))
			best_hull = curr_order;
		REP(i, n)
			if(not taken[i]) {
				taken[i] = true;
				curr_order.emplace_back(i);
				backtrack();
				curr_order.pop_back();
				taken[i] = false;
			}
	};
	backtrack();
	debug(best_hull);

	vector<P> brute;
	for(int i : best_hull)
		brute.emplace_back(in[i]);

	bool all_colinear = n > 1;
	REP(i, n)
		REP(j, n)
			if(dir(in[0], in[i], in[j]) != 0)
				all_colinear = false;
	if(all_colinear)
		brute = {*min_element(in.begin(), in.end()), *max_element(in.begin(), in.end())};

	vector<P> wzorc = hull(in);
	debug(brute, wzorc);
	assert(brute == wzorc);
}
