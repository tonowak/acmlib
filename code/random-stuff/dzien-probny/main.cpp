/*
 * Opis: int128, rand(), mt19937, chrono, clock(), time, ordered_set, float128
 */

void test_int128() {
	__int128_t x = (1llu << 62);
	x *= x;
	string s;
	while(x) {
		s += char(x % 10 + '0');
		x /= 10;
	}
	assert(s == "61231558446921906466935685523974676212");
}

void test_float128() {
	__float128 x = 4.2;
	assert(abs(double(x * x) - double(4.2 * 4.2)) < 1e-9);
}

void test_clock() {
	long seeed = chrono::system_clock::now().time_since_epoch().count();
	auto start = chrono::system_clock::now();

	while(true) {
		auto end = chrono::system_clock::now();
		int ms = int(chrono::duration_cast<chrono::milliseconds>(end - start).count());
		if(ms > 420)
			break;
	}
}

void test_rd() {
	mt19937_64 rng(0);
	auto rd = [&](int l, int r) {
		return uniform_int_distribution<int>(l, r)(rng);
	};
	assert(rd(0, 0) == 0);
}

#include "../../data-structures/ordered-set/main.cpp"

void test_policy() {
	ordered_set<int> s;
	s.insert(1);
	s.insert(2);
	assert(s.order_of_key(1) == 0);
	assert(*s.find_by_order(1) == 2);
}
