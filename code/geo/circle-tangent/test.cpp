#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	while(true) {
		P p(rd(-10, 10), rd(-10, 10));
		D r = rd(1, 10);
		if(sign(dot(p, p) - r * r) <= 0)
			continue;

		P o(rd(-10, 10), rd(-10, 10));
		p += o;

		auto [p0, p1] = tangents_to_circle(o, r, p);
		debug(p, r, o, p0, p1);
		auto dist2 = [&](P x) {
			return dot(x, x);
		};
		assert(equal(abs(p0 - o), r));
		assert(equal(abs(p1 - o), r));
		assert(not equal(p0, p1));
		assert(equal(dist2(p - o), dist2(p0 - o) + dist2(p - p0)));
		assert(equal(dist2(p - o), dist2(p1 - o) + dist2(p - p1)));
		break;
	}
}
