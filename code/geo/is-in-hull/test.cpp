#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n;
	vector<P> in;
	while(true) {
		n = rd(1, 10);
		in.resize(n);
		for(auto &p : in)
			p = P(rd(-10, 10), rd(-10, 10));
		bool valid = true;
		REP(i, n)
			if(dir(in[i], in[(i + 1) % n], in[(i + 2) % n]) > 0)
				valid = false;
		REP(i, n)
			REP(j, n)
				if(dir(in[i], in[(i + 1) % n], in[j]) > 0)
					valid = false;
		REP(i, n)
			REP(j, i)
				if(equal(in[i], in[j]))
					valid = false;
		REP(i, n)
			REP(j, i)
				REP(k, j)
					if(dir(in[i], in[j], in[k]) == 0)
						valid = false;
		if(valid)
			break;
	}
	debug(in);

	REP(queries, 10) {
		bool can_on_edge = rd(0, 1);
		P p = P(rd(-10, 10), rd(-10, 10));
		debug(can_on_edge, p);

		bool is_on_edge = false;
		REP(i, n)
			if(on_segment(in[i], in[(i + 1) % n], p))
				is_on_edge = true;
		debug(is_on_edge);
		
		int inter_cnt = 0;
		REP(i, n)
			if(is_intersection_segment(p, P(100, p.y + 1), in[i], in[(i + 1) % n]))
				++inter_cnt;
		debug(inter_cnt);

		bool brute_ans = (is_on_edge ? can_on_edge : inter_cnt % 2 == 1);
		bool wzorc_ans = is_in_hull(in, p, can_on_edge);
		debug(brute_ans, wzorc_ans);
		assert(brute_ans == wzorc_ans);
	}
}
