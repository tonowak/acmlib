#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

D rd_double(D l, D r) {
	return uniform_real_distribution<D>(l, r)(tester_rng);
}

void test() {
	//int mx = 1e9;
	int mx = 1;
	array<D, 6> in;
	REP(i, 6)
		in[i] = rd_double(i % 3 == 2 ? 0 : -mx, mx);
	auto vec = circle_circle(in[0], in[1], in[2], in[3], in[4], in[5]);
	debug(in, vec);

	if(equal(in[0], in[3]) and equal(in[1], in[4])) {
		if(equal(in[2], in[5]))
			assert(ssize(vec) == 3);
		else
			assert(ssize(vec) == 0);
	}

	P p1(in[0], in[1]), p2(in[3], in[4]);

	D d = dist(P(in[0], in[1]), P(in[3], in[4]));
	debug(d);
	int sign1 = sign(abs(in[2] - in[5]) - d), sign2 = sign(d - in[2] - in[5]);
	if(sign1 == 0 or sign2 == 0)
		assert(ssize(vec) == 1);
	else if(sign1 > 0 or sign2 > 0)
		assert(ssize(vec) == 0);
	else
		assert(ssize(vec) == 2);

	for(P p : vec)
		for(int i : {0, 3}) {
			D di = dist(p, P(in[i], in[i + 1]));
			assert(equal(di, in[i + 2]));
		}
}
