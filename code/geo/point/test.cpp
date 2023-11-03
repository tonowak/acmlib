#include "before_bits.cpp"
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

ostream& operator<<(ostream& os, pair<auto, auto> p) {
	return os << "(" << p.first << ", " << p.second << ")\n";
}

#include "main.cpp"

void f([[maybe_unused]] P p) {}

void assert_eq(D a, D b) {
	assert(abs(a - b) <= eps);
}

int main() {
	P p = {2, 3};
	// assign operator
	p = {6, 9};
	assert(equal(p.x(), 6) && equal(p.y(), 9));

	p = P(5, 3);
	assert(equal(p.x(), 5) && equal(p.y(), 3));

	P squared = p * p;
	// (5 + 3i) * (5 + 3i) = 25 - 9 + 30i = (16, 30)
	assert(equal(squared.x(), 16) && equal(squared.y(), 30));

	// implicit casting std::complex -> Point
	f(p * p);
	ofstream o("/dev/null");
	o << p * p << "\n";

	p = P{3, 4};
	// assert(abs(p) == 5); this fails... dont use ints

	assert_eq(abs(P{3, 4}), 5);
	assert_eq(cross({1, 0}, {0, 1}), 1);

	auto lambda = [&]{ return p; };
	auto q = lambda();
	q = P(q.x() + 1, q.y());
	assert(equal(p.x() + 1, q.x()));

	cout << "OK\n";
}
