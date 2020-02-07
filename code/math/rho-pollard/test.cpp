#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool test(int ms) {
	LL a;
	cin >> a;
	debug(factor(a));
	return true;
}
