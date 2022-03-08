#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

struct Matrix {
	vector<vector<int>> m;
	Matrix() {
		m = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	}
	Matrix(vector<vector<int>> _m) : m(_m) {}
	Matrix operator*(const Matrix& other) {
		auto res = vector (3, vector (3, 0));
		REP(i,3) {
			REP(j,3) {
				REP(k,3) {
					res[i][j] += this->m[i][k] * other.m[k][j];
				}
			}
		}
		return Matrix(res);
	}
	bool operator==(const Matrix& other) {
		REP(i,3) {
			REP(j,3) {
				if (this->m[i][j] != other.m[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
};
ostream& operator<<(ostream&o, const Matrix& matrix) {
	return o << matrix.m;
}

void test() {
	AssocQueue<int> q1([](int a, int b){ return min(a, b);}, (1 << 30));
	AssocQueue<Matrix> q2([](Matrix a, Matrix b){ return a * b;});
	AssocQueue<int> q3([](int a, int b){ return min(a, b);}, numeric_limits<int>::max());

	int n = rd(1, 30);
	debug(n);
	vector<Matrix> v(n);
	auto los = [&] {
		Matrix res{};
		REP(i,3) {
			REP(j,3) {
				res.m[i][j] = rd(-2, 2);
			}
		}
		return res;
	};
	REP(i,n) {
		v[i] = los();
	}
	debug(v);
	auto helper = [&](int a, int b) {
		Matrix m;
		FOR(i,a,b) {
			m = m * v[i];
		}
		debug(a, b, m);
		return m;
	};
	int cntl = n;
	int cntr = n;
	int l = 0, r = -1;
	AssocQueue<Matrix> que([&](Matrix a, Matrix b) { return a * b;});
	while (cntl + cntr > 0) {
		int type = rd(0,5);
		debug(type, ssize(que.s1), ssize(que.s2));
		if (type == 0) {
			if (cntr == 0) continue;
			++r;
			--cntr;
			debug(v[r]);
			que.emplace(v[r]);
		}
		else if (type == 1) {
			if (l > r) continue;
			debug("pop");
			++l;
			--cntl;
			que.pop();
		}
		else if (type == 2) {
			if (l > r) continue;
			debug(que.calc());
			assert(helper(l, r) == que.calc());
		}
		else if (type == 3) {
			if (l > r) continue;
			debug(v[l], que.front());
			assert(v[l] == que.front());
		}
		else if (type == 4) {
			debug("size");
			assert(r - l + 1 == que.size());
		}
		else if (type == 5) {
			if (rd(0, 100) != 0) continue;
			cntr = cntl = n;
			r = -1;
			l = 0;
			debug("clear");
			que.clear();
		}
	}
}
