#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
// #include "../convex-hull/main.cpp"

void test() {
	int n = rd(1, 10);
	vector<P> in(n);
	for(auto &p : in)
		p = P(rd(-10, 10), rd(-10, 10));
	debug(in);
	in = hull(in);
	debug(in);
	n = ssize(in);

	REP(queries, 10) {
		bool can_on_edge = rd(0, 1);
		P p = P(rd(-10, 10), rd(-10, 10));

		bool is_on_edge = false;
		REP(i, n)
			if(on_segment(in[i], in[(i + 1) % n], p))
				is_on_edge = true;
		
		int inter_cnt = 0;
		REP(i, n)
			if(is_intersection_segment(p, P(100, p.y + 1), in[i], in[(i + 1) % n]))
				++inter_cnt;

		bool brute_ans = (is_on_edge ? can_on_edge : inter_cnt % 2 == 1);
		bool wzorc_ans = is_in_hull(in, p, can_on_edge);
		assert(brute_ans == wzorc_ans);
	}
}
