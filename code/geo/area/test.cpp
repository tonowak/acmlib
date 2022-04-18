#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	vector<P> poly = {
		P(2, -1),
		P(4, 1),
		P(4, -3),
		P(6, -3),
		P(6, 2),
		P(1, 2),
		P(1, 3),
		P(6, 3),
		P(6, 5),
		P(-3, 5),
		P(-3, 3),
		P(-1, -1),
	};
	assert(equal(area(poly), 18 + 4 + 2 + 5 + 6 + 2 + 10));

	P p0 = P(3, 1), p1 = P(1, 4), p2 = P(6, 6);
	D area_should_be = 3 + 2 + 4.5;
	assert(equal(area(dist(p0, p1), dist(p0, p2), dist(p1, p2)), area_should_be));
	assert(equal(area(vector{p0, p1, p2}), area_should_be));
	exit(0);
}
