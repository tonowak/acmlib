#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int mx = 10;
	auto rd_p = [&]() -> P {
		return {D(rd(0, mx)), D(rd(0, mx))};
	};
	auto a = rd_p();
	auto b = rd_p();
	auto c = rd_p();
	auto d = rd_p();
	bool is_inter_segment = is_intersection_segment(a, b, c, d);
	auto intersections_segment = intersect_segments(a, b, c, d);
	debug(a, b, c, d, is_inter_segment, intersections_segment);
	assert(is_inter_segment == not intersections_segment.empty());
}
