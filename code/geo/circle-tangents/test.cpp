#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	P p0(rd(-10, 10), rd(-10, 10));
	P p1(rd(-10, 10), rd(-10, 10));
	D r0 = rd(0, 10);
	D r1 = rd(0, 10);
	bool inside = rd(0, 1);
	debug(p0, p1, r0, r1, inside);

	vector got = circle_tangents(p0, r0, p1, r1, inside);
	debug(got);

	int sgn = sign(dist(p0, p1) - (inside ? r0 + r1 : abs(r0 - r1)));
	debug(sgn);
	if(equal(p0, p1))
		assert(got.empty());
	else
		assert(ssize(got) == 1 + sgn);

	if(ssize(got) == 1) {
		assert(equal(got[0].first, got[0].second));
		assert(dir(p0, p1, got[0].first) == 0 and 
				equal(dist(p0, got[0].first), r0) and 
				equal(dist(p1, got[0].first), r1));
	}
	else if(ssize(got) == 2) {
		for(int d : {0, 1}) {
			assert(equal(dist(p0, got[d].first), r0));
			assert(equal(dist(p1, got[d].second), r1));
			assert(equal(dot(p0 - got[d].first, got[d].first - got[d].second), 0));
			assert(equal(dot(p1 - got[d].second, got[d].first - got[d].second), 0));
		}

		if(equal(r0, 0))
			assert(equal(got[0].first, got[1].first));
		if(equal(r1, 0))
			assert(equal(got[0].second, got[1].second));
	}
}
