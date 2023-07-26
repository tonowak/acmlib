#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#include "main.cpp"

void f([[maybe_unused]] Point<LL> p) {}

ostream& operator<<(ostream& os, Point<LL> p) {
	return os << "(" << p.x << ", " << p.y << ")\n";
}

void assert_eq(D a, D b) {
	assert(abs(a - b) <= eps);
}

int main() {
	Point<LL> p = {2, 3};
	// assign operator
	p = Point<LL>{6, 9};
	assert(p.x == 6 && p.y == 9);

	p.x = 5;
	p.y = 3;
	assert(p.x == 5 && p.y == 3);

	Point squared = p * p;
	// (5 + 3i) * (5 + 3i) = 25 - 9 + 30i = (16, 30)
	assert(squared.x == 16 && squared.y == 30);

	// implicit casting std::complex -> Point
	f(p * p);
	ofstream o("/dev/null");
	o << p * p << "\n";

	p = Point<LL>{3, 4};
	// assert(abs(p) == 5); this fails... dont use ints

	assert_eq(abs(Point<double>{3, 4}), 5);
	assert_eq(cross({1, 0}, {0, 1}), 1);

	auto lambda = [&]{ return p; };
	auto q = lambda();
	q.x += 1;
	assert(p.x + 1 == q.x);

	cout << "OK\n";
}
