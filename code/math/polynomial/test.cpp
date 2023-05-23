#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto get_vec = [&](int a, int b) {
		int n = rd(a, b);
		vector<int> v(n);
		for(int &e : v)
			e = rd(0, mod - 1);
		return v;
	};

	auto eq = [&](vi a, vi b) {
		int s = max(ssize(a), ssize(b));
		a.resize(s), b.resize(s);
		return a == b;
	};

	auto add_vi = [&](vi a, vi b) {
		a.resize(max(ssize(a), ssize(b)));
		REP(i, ssize(b))
			a[i] = add(a[i], b[i]);
		return a;
	};

	auto brute_eval = [&](vi a, int x) {
		reverse(a.begin(), a.end());
		int ret = 0;
		for (auto e : a)
			ret = add(mul(ret, x), e);
		return ret;
	};

	const int mn = 20;
	const int mk = 20;

	{ // powi_slow
		auto a = get_vec(0, mn);
		int n = rd(1, mn);
		int k = rd(0, mk);
		vi b{1};
		REP(i, k)
			b = mod_xn(conv(b, a), n);
		assert(eq(b, powi_slow(a, k, n)));
	}

	{ // powi_deg
		auto a = get_vec(1, mn);
		a[0] = rd(1, mod - 1);
		int n = rd(1, mn);
		int k = rd(0, mk);
		assert(eq(powi_deg(a, k, n), powi_slow(a, k, n)));
	}

	{ // sqrt
		auto a = get_vec(1, mn);
		a[0] = 1;
		int n = rd(1, mn);
		auto sq = sqrt(a, n);
		assert(eq(mod_xn(conv(sq, sq), n), mod_xn(a, n)));
	}

	{ // inv
		auto a = get_vec(1, mn);
		a[0] = rd(1, mod - 1);
		int n = rd(1, mn);
		auto inva = inv(a, n);
		assert(eq(mod_xn(conv(a, inva), n), {1}));
	}

	{ // log
		auto a = get_vec(1, mn);
		a[0] = 1;
		int n = rd(1, mn);
		assert(eq(mod_xn(a, n), exp(log(a, n), n)));
	}

	{ // exp
		auto a = get_vec(0, mn);
		if (ssize(a))
			a[0] = 0;
		int n = rd(1, mn);
		vi b{0}, c{1};
		REP(i, n) {
			b = add_vi(b, c);
			c = mod_xn(conv(c, a), n);
			int invi = inv(i + 1);
			for(auto& e : c) e = mul(e, invi);
		}
		assert(eq(mod_xn(b, n), exp(a, n)));
	}

	{ // powi
		auto a = get_vec(0, mn);
		int n = rd(1, mn);
		int k = rd(0, mk);
		assert(eq(powi(a, k, n), powi_slow(a, k, n)));
	}

	{ // div
		auto a = get_vec(0, mn);
		auto b = get_vec(1, mn);
		auto [c, d] = div(a, b);
		assert(a == add_vi(conv(c, b), d));
	}

	{ // eval
		const int L = rd(0, 100) ? mn : 1000;
		auto a = get_vec(0, L);
		auto x = get_vec(0, L);
		auto y = eval(a, x);
		assert(ssize(x) == ssize(y));
		REP(i, ssize(x))
			assert(brute_eval(a, x[i]) == y[i]);
	}

	{ // inter
		// TODO
	}
}
