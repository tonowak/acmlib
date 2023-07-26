/*
 * Opis: Rzeczy do przetestowania w dzień próbny.
 */

// alternatywne mnożenie LL, gdyby na wypadek gdyby nie było __int128
LL llmul(LL a, LL b, LL m) {
	return (a * b - (LL)((long double) a * b / m) * m + m) % m;
}

void test_int128() {
	__int128 x = (1llu << 62);
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
	(void) seeed;
	auto start = chrono::system_clock::now();

	while(true) {
		auto end = chrono::system_clock::now();
		int ms = int(chrono::duration_cast<chrono::milliseconds>(end - start).count());
		if(ms > 420)
			break;
	}
}

void test_rd() {
	// czy jest sens to testowac?
	mt19937_64 my_rng(0);
	auto rd = [&](int l, int r) {
		return uniform_int_distribution<int>(l, r)(my_rng);
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

void test_math() {
	constexpr long double pi = acosl(-1);
	assert(3.14 < pi && pi < 3.15);
}
