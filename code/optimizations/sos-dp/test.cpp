#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 10);
	int N = (1 << n);
	vector<LL> A(N), pod(N), nad(N);
	REP(i,N) A[i] = rd(0, int(1e9));
	REP(i,N)
		REP(j,N)
			if ((i & j) == j) {
				pod[i] += A[j];
				nad[j] += A[i];
			}
	assert(pod == sos_dp(n, A));
	assert(nad == sos_dp(n, A, true));
}
