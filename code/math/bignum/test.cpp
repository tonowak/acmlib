#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

ostream& operator<<(ostream& o, __int128_t x) {
	vector<int> v;
	if (x == 0) v.emplace_back(0);
	while (x > 0) {
		v.emplace_back(x % 10);
		x /= 10;
	}
	reverse(v.begin(), v.end());
	for (auto xd : v) {
		o << xd;
	}
	return o;
}

template<typename T1, typename T2>
bool issame(T1 num, T2 x) {
	stringstream snum;
	snum << num;
	stringstream sx;
	sx << x;
	return snum.str() == sx.str();
}

using T = __int128_t;
constexpr T INF = (__int128_t)(1ll << 60) * (1ll << 60);
T gcd(T a, T b) {
	if (b == T(0)) {
		return a;
	}
	return gcd(b, a % b);
}

void test() {
	vector<Num> vnum{1, 2, 4, 11};
	vector<T> vt{1, 2, 4, 11};
	set<T> st{1, 2, 4, 11};
	int opcnt = rd(1, 1000);
	map<int,int> cnt;
	while (opcnt) {
		int x = rd(0, ssize(vnum) - 1);
		int y = rd(0, ssize(vnum) - 1);
		int type = rd(0, 11);
		int sp = ssize(vt);
		if (type == 0) {
			if (INF - vt[x] < vt[y]) continue;
			vt.emplace_back(vt[x] + vt[y]);
			vnum.emplace_back(vnum[x] + vnum[y]);
		}
		else if (type == 1) {
			assert((vt[x] < vt[y]) == (vnum[x] < vnum[y]));
		}
		else if (type == 2) {
			assert((vt[x] == vt[y]) == (vnum[x] == vnum[y]));
		}
		else if (type == 3) {
			assert((vt[x] <= vt[y]) == (vnum[x] <= vnum[y]));
		}
		else if (type == 4) {
			if (vt[x] < vt[y]) continue;
			vt.emplace_back(vt[x] - vt[y]);
			vnum.emplace_back(vnum[x] - vnum[y]);
		}
		else if (type == 5) {
			int val = rd(1, 1e9);
			if (INF / val < vt[x]) continue;
			vt.emplace_back(vt[x] * val);
			vnum.emplace_back(vnum[x] * val);
		}
		else if (type == 6) {
			if (vt[x] != 0 and INF / vt[x] < vt[y]) continue;
			vt.emplace_back(vt[x] * vt[y]);
			vnum.emplace_back(vnum[x] * vnum[y]);
		}
		else if (type == 7) {
			int val = rd(1, 1e9);
			vt.emplace_back(vt[x] / val);
			vnum.emplace_back(vnum[x] / val);
		}
		else if (type == 8) {
			if (vt[y] == 0) continue;
			vt.emplace_back(vt[x] / vt[y]);
			vnum.emplace_back(vnum[x] / vnum[y]);
		}
		else if (type == 9) {
			if (vt[y] == 0) continue;
			vt.emplace_back(vt[x] % vt[y]);
			vnum.emplace_back(vnum[x] % vnum[y]);
		}
		else if (type == 10) {
			int val = rd(1, 1e9);
			vt.emplace_back(vt[x] % val);
			vnum.emplace_back(vnum[x] % val);
		}
		else if (type == 11) {
			if (vt[x] == 0 and vt[y] == 0) continue;
			vt.emplace_back(gcd(vt[x], vt[y]));
			vnum.emplace_back(nwd(vnum[x], vnum[y]));
		}
		if (sp != ssize(vt)) {
			if (st.find(vt.back()) == st.end()) {
				st.emplace(vt.back());
			}
			else {
				vt.pop_back();
				vnum.pop_back();
			}
		}
		assert(issame(vt.back(), vnum.back()));
		--opcnt;
		++cnt[type];
		debug(vnum);
	}
	debug(cnt);
}
