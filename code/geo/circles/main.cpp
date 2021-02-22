/*
 * Opis: Przecięcia okręgu oraz prostej ax+by+c=0 oraz przecięcia okręgu oraz okręgu.
 * Użycie: ssize(circle_circle(...)) == 3 to jest nieskończenie wiele rozwiązań
 */
#include "../point/main.cpp"
using D = Double;

vector<P> circle_line(D r, D a, D b, D c) {
	D len_ab = a * a + b * b,
	  x0 = -a * c / len_ab,
	  y0 = -b * c / len_ab,
	  d = r * r - c * c / len_ab,
	  mult = sqrt(d / len_ab);
	if(sign(d) < 0)
		return {};
	else if(sign(d) == 0)
		return {{x0, y0}};
	return {
		{x0 + b * mult, y0 - a * mult},
		{x0 - b * mult, y0 + a * mult}
	};
}
vector<P> circle_line(D x, D y, D r, D a, D b, D c) {
	return circle_line(r, a, b, c + (a * x + b * y));
}
vector<P> circle_circle(D x1, D y1, D r1, D x2, D y2, D r2) {
	x2 -= x1;
	y2 -= y1;
	// now x1 = y1 = 0;
	if(sign(x2) == 0 and sign(y2) == 0) {
		if(equal(r1, r2))
			return {{0, 0}, {0, 0}, {0, 0}}; // inf points
		else
			return {};
	}
	auto vec = circle_line(r1, -2 * x2, -2 * y2,
			x2 * x2 + y2 * y2 + r1 * r1 - r2 * r2);
	for(P &p : vec)
		p += P(x1, y1);
	return vec;
}
