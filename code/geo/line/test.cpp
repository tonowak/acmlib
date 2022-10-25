#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto rd_D = [&] {
		return D(rd(-1e9, 1e9)) / 1e6;
	};
	Line line(rd_D(), rd_D(), rd_D());

	auto [s, t] = line.get_pts();
	Line line2(s, t);
	assert(equal(line.A * line2.B, line2.A * line.B)
			and equal(line.B * line2.C, line2.B * line.C)
			and equal(line.C * line2.A, line2.C * line.A));

	P p(rd_D(), rd_D());
	auto dist1 = line.dist(p);
	auto angle = rd_D();
	P rot(cos(angle), sin(angle));
	Line line3(s * rot, t * rot);
	auto dist3 = line3.dist(p * rot);
	assert(equal(dist1, dist3));

	P d(rd_D(), rd_D());
	auto dist2 = line2.dist(d);
	assert(dist2 <= dist(s, d) and dist2 <= dist(t, d));
}
