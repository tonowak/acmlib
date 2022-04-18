#include "../../utils/headers/main.cpp"
#include "main.cpp"


int main() {
#ifndef TESTING
    // tests needs gurobipy python package, so they are disabled by default
    return 0;
#endif 

    int n, m;
    cin >> n >> m;
    Simplex lp(n, m);
    REP(i, m) {
        REP(j, n)
            cin >> lp.A[i][j];
        cin >> lp.b[i];
    }
    REP(i, n)
        cin >> lp.c[i];

    assert(lp.solve());
    cout << lp.res << "\n";
}
