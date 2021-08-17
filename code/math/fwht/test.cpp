#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<int> get_random_a(int n = -1) {
	if(n == -1)
		n = 1 << rd(0, 4);
	vector<int> a(n);
	for(int &ai : a)
		ai = rd(-5, 5);
	return a;
}

void test_fwht_or() {
	vector<int> a = get_random_a();
	int n = ssize(a);
	vector<int> should_be(n);
	REP(i, n)
		REP(j, n)
			if((j | i) == i)
				should_be[i] += a[j];
	assert(should_be == fwht_or(a));
}

void test_ifwht_or() {
	vector<int> a = get_random_a();
	assert(ifwht_or(fwht_or(a)) == a);
}

void test_convolution_or() {
	vector<int> a = get_random_a();
	int n = ssize(a);
	vector<int> b = get_random_a(n);
	vector<int> should_be(n);
	REP(i, n)
		REP(j, n)
			REP(k, n)
				if((j | k) == i)
					should_be[i] += a[j] * b[k];
	assert(should_be == convolution_or(a, b));
}

void test_fwht_and() {
	vector<int> a = get_random_a();
	int n = ssize(a);
	vector<int> should_be(n);
	REP(i, n)
		REP(j, n)
			if((j & i) == i)
				should_be[i] += a[j];
	assert(should_be == fwht_and(a));
}

void test_ifwht_and() {
	vector<int> a = get_random_a();
	assert(ifwht_and(fwht_and(a)) == a);
}

void test_convolution_and() {
	vector<int> a = get_random_a();
	int n = ssize(a);
	vector<int> b = get_random_a(n);
	vector<int> should_be(n);
	REP(i, n)
		REP(j, n)
			REP(k, n)
				if((j & k) == i)
					should_be[i] += a[j] * b[k];
	assert(should_be == convolution_and(a, b));
}

void test_fwht_xor() {
	vector<int> a = get_random_a();
	int n = ssize(a);
	vector<int> should_be(n);
	REP(i, n)
		REP(j, n)
			if(__builtin_popcount(i & j) % 2 == 0)
				should_be[i] += a[j];
			else
				should_be[i] -= a[j];
	assert(should_be == fwht_xor(a));
}

void test_ifwht_xor() {
	vector<int> a = get_random_a();
	assert(ifwht_xor(fwht_xor(a)) == a);
}

void test_convolution_xor() {
	vector<int> a = get_random_a();
	int n = ssize(a);
	vector<int> b = get_random_a(n);
	vector<int> should_be(n);
	REP(i, n)
		REP(j, n)
			REP(k, n)
				if((j ^ k) == i)
					should_be[i] += a[j] * b[k];
	assert(should_be == convolution_xor(a, b));
}

void test() {
	test_fwht_or();
	test_ifwht_or();
	test_convolution_or();
	test_fwht_and();
	test_ifwht_and();
	test_convolution_and();
	test_fwht_xor();
	test_ifwht_xor();
	test_convolution_xor();
}
