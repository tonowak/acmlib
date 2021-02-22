#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector</*LL*/double> get_poly() {
	/*
	int n = rd(1, 1e3);
	vector<LL> A(n);
	REP(i, n) A[i] = rd(0, 1e9);
	return A;
	*/

	int n; cin >> n;
	vector<double> A(n);
	REP(i, n) cin >> A[i];
	return A;
}

int mod = 1e9 + 7;
vector<LL> mul(vector<LL> A, vector<LL> B) {
	vector<LL> res(ssize(A) + ssize(B) - 1);
	REP(i, ssize(A)) REP(j, ssize(B))
		res[i + j] = (res[i + j] + A[i] * B[j]) % mod;
	return res;
}

void test() { 
	/*
	vector<LL> A = get_poly(), B = get_poly();
	debug(A, B);
	debug(mul(A, B));
	debug(conv_mod(A, B, mod));
	return mul(A, B) != conv_mod(A, B, mod);
	*/
	
	vector<double> A = get_poly(), B = get_poly();
	debug(A, B);
	debug(conv(A, B));
}
