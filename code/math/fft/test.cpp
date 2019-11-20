#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<int> get_poly() {
	int n = rd(1, 1e3);
	vector<int> A(n);
	REP(i, n) A[i] = rd(0, 1e3);
	return A;
}

vector<int> mul(vector<int> A, vector<int> B) {
	vector<int> res(size(A) + size(B) - 1);
	REP(i, size(A)) REP(j, size(B))
		res[i + j] += A[i] * B[j];
	return res;
}

bool test(int ms) {
	vector<int> A = get_poly(), B = get_poly();
	debug(A, B);
	debug(mul(A, B));
	debug(conv_int(A, B));
	return mul(A, B) != conv_int(A, B);
}
