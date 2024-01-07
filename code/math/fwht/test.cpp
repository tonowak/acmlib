#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<int> get_random_a(int n = -1) {
	if(n == -1)
		n = 1 << rd(0, 4);
	vector<int> a(n);
	for(int &ai : a)
		ai = rd(0, mod - 1);
	return a;
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
					should_be[i] = add(should_be[i], mul(a[j], b[k]));
	assert(should_be == convolution_or(a, b));
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
					should_be[i] = add(should_be[i], mul(a[j], b[k]));
	assert(should_be == convolution_and(a, b));
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
					should_be[i] = add(should_be[i], mul(a[j], b[k]));
	assert(should_be == convolution_xor(a, b));
}

void test() {
	test_convolution_or();
	test_convolution_and();
	test_convolution_xor();
}
