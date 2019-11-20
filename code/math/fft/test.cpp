#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<LL> get_poly() {
	int n = rd(1, 1e3);
	vector<LL> A(n);
	REP(i, n) A[i] = rd(0, 1e9);
	return A;
}

int mod = 1e9 + 7;
vector<LL> mul(vector<LL> A, vector<LL> B) {
	vector<LL> res(size(A) + size(B) - 1);
	REP(i, size(A)) REP(j, size(B))
		res[i + j] = (res[i + j] + A[i] * B[j]) % mod;
	return res;
}

bool test(int ms) {
	vector<LL> A = get_poly(), B = get_poly();
	debug(A, B);
	debug(mul(A, B));
	debug(conv_mod(A, B, mod));
	return mul(A, B) != conv_mod(A, B, mod);
}
