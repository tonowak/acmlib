/*
 * Opis: Solver do programowania liniowego
 * Czas: O(szybko)
 * Użycie:
 *   Simplex(n, m) tworzy lpsolver z n zmiennymi i m ograniczeniami
 *   Rozwiązuje max cx przy Ax <= b
 */

#define FIND(n, expr) [&] { REP(i, n) if(expr) return i; return -1; }()

struct Simplex {
    using T = double;
    const T eps = 1e-9, inf = 1/.0;
    int n, m;
    vector<int> N, B;
    vector<vector<T>> A;
    vector<T> b, c;
    T res = 0;

    Simplex(int vars, int eqs)
        : n(vars), m(eqs), N(n), B(m), A(m, vector<T>(n)), b(m), c(n) {
        REP(i, n) N[i] = i; 
        REP(i, m) B[i] = n + i;
    }

    void pivot(int eq, int var) {
        T coef = 1 / A[eq][var], k;
        REP(i, n)
            if(abs(A[eq][i]) > eps) A[eq][i] *= coef;
        A[eq][var] *= coef, b[eq] *= coef;
        REP(r, m) if(r != eq && abs(A[r][var]) > eps) {
            k = -A[r][var], A[r][var] = 0;
            REP(i, n) A[r][i] += k * A[eq][i];
            b[r] += k * b[eq];
        }
        k = c[var], c[var] = 0;
        REP(i, n) c[i] -= k * A[eq][i];
        res += k * b[eq];
        swap(B[eq], N[var]);
    }

    bool solve() {
        int eq, var;
        while(true) {
            if((eq = FIND(m, b[i] < -eps)) == -1) break;
            if((var = FIND(n, A[eq][i] < -eps)) == -1) {
                res = -inf; // no solution
                return false;
            }
            pivot(eq, var);
        }
        while(true) {
            if((var = FIND(n, c[i] > eps)) == -1) break;
            eq = -1;
            REP(i, m) if(A[i][var] > eps
                && (eq == -1 || b[i] / A[i][var] < b[eq] / A[eq][var]))
                eq = i;
            if(eq == -1) {
                res = inf; // unbound
                return false;
            }
            pivot(eq, var);
        }
        return true;
    }

    vector<T> get_vars() {
        vector<T> vars(n);
        REP(i, m)
            if(B[i] < n) vars[B[i]] = b[i];
        return vars;
    }
};
