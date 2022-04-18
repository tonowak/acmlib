#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

struct Brute {
	int n;
	vector<pair<int,bool>> vsetvalue;
	vector<tuple<int,bool,int,bool>> veither;
	vector<vector<pair<int,bool>>> vatmostone;

	Brute(int _n) : n(_n) {}

	void either(int a, bool b, int c, bool d) {
		veither.emplace_back(a, b, c, d);
	}

	void set_value(int a, bool b) {
		vsetvalue.emplace_back(a, b);
	}

	void at_most_one(vector<pair<int,bool>> v) {
		vatmostone.emplace_back(v);
	}

	bool does_satisfy(vector<int> v) {
		for (auto [a, b] : vsetvalue)
			if (v[a] != b)
				return false;
		for (auto [a, b, c, d] : veither)
			if (v[a] != b and v[c] != d)
				return false;
		for (auto x : vatmostone) {
			int cnt = 0;
			for (auto [a, b] : x)
				cnt += (v[a] == b);
			if (cnt > 1)
				return false;
		}
		return true;
	}

	bool solve() {
		REP(i,(1<<n)) {
			vector v(n, 0);
			REP(j,n)
				if ((i >> j) & 1)
					v[j] = 1;
			if (does_satisfy(v))
				return true;
		}
		return false;
	}
};

void test() {
	int n = rd(2, 10);
	int m = rd(0, 10);

	auto var = [&] {
		int x = rd(0, n - 1);
		if (rd(0, 1))
			return tuple<int,int,bool>{x, x, true};
		else
			return tuple<int,int,bool>{~x, x, false};
	};

	TwoSat ts(n);
	Brute br(n);
	REP(ii,m) {
		int type = rd(0, 2);
		if (type == 0) {
			auto [a, b, c] = var();
			auto [d, e, f] = var();
			ts.either(a, d);
			br.either(b, c, e, f);
		}
		else if (type == 1) {
			auto [a, b, c] = var();
			ts.set_value(a);
			br.set_value(b, c);
		}
		else if (type == 2) {
			int k = rd(0, n);
			vector<int> vts(k);
			vector<pair<int,bool>> vbr(k);
			REP(i,k) {
				auto [a, b, c] = var();
				vts[i] = a;
				vbr[i] = {b, c};
			}
			ts.at_most_one(vts);
			br.at_most_one(vbr);
		}
	}
	assert(ts.solve() == br.solve());
	if (ts.solve()) {
		assert(br.does_satisfy(ts.values));
	}
	debug(ts.solve(), ts.values);
}
