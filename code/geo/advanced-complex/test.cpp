#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"
#include "../line/main.cpp"

void test() {
	auto rd_D = [&] {
		return D(rd(-1e9, 1e9)) / 1e8;
	};
	auto rd_P = [&] {
		return P(rd_D(), rd_D());
	};
	auto rel_equal_D = [&](D a, D b) {
		return equal(a, b) or (a * b >= 0 and max(abs(a), abs(b)) <= (1. + eps) * min(abs(a), abs(b)));
	};
	auto rel_equal_P = [&](P a, P b) {
		return rel_equal_D(a.x, b.x) and rel_equal_D(a.y, b.y);
	};
	auto to_close = [&](P a, P b) {
		return dist(a, b) < 0.001;
	};

	auto a = rd_P(), b = rd_P();
	auto line = Line(a, b);
	if (not to_close(a, b))
		assert(rel_equal_D(line.get_dir().first, slope(a, b)));

	auto p = rd_P();
	if (not to_close(a, b))
		assert(is_parallel(a, b, a + p, b + p));

	auto r = reflect(p, a, b);
	if (not to_close(p, r))
		assert(is_perpendicular(a, b, p, r));
	assert(equal(line.directed_dist(p), -line.directed_dist(r)));
	assert(equal(line.dist(p), line.dist(r)));

	auto c = rd_P(), d = rd_P();
	assert(not is_perpendicular(a, b, c, d));
	assert(not is_parallel(a, b, c, d));

	if (not to_close(a, b)) {
		assert(is_parallel(a, b, p, parallel(a, b, p)));
		if (not to_close(p, perpendicular(a, b, p)))
				assert(is_perpendicular(a, b, p, perpendicular(a, b, p)));
	}

	auto cc = centro(a, b, c);
	assert(rel_equal_P((a + b) / 2.0L, intersection(a, b, c, cc)));

	assert(rel_equal_P(project(p, a, b), intersection(a, b, p, r)));

	auto t = p;
	const int st = rd(1, 10);
	REP(i, st) {
		t = rotate(t, a, 2.0L * pi / st);
		assert((i != st - 1) ^ rel_equal_P(t, p));
	}

	assert(rel_equal_D(angle(a, b, c), acos((dot(a - b, c - b)) / dist(a, b) / dist(c, b))));
}
