/*
 * Opis: Hashowanie z małą stałą. Można zmienić bazę (jeśli serio trzeba).
 */
struct Hashing {
	vector<LL> ha, pw;
	static constexpr LL mod = (1ll << 61) - 1;
	LL reduce(LL x) { return x >= mod ? x - mod : x; }
	LL mul(LL a, LL b) {
		const auto c = __int128(a) * b;
		return reduce(LL(c & mod) + LL(c >> 61));
	}
	Hashing(const vector<int> &str, const int base = 37) {
		int len = ssize(str);
		ha.resize(len + 1);
		pw.resize(len + 1, 1);
		REP(i, len) {
			ha[i + 1] = reduce(mul(ha[i], base) + str[i] + 1);
			pw[i + 1] = mul(pw[i], base);
		}
	}
	LL operator()(int l, int r) {
		return reduce(ha[r + 1] - mul(ha[l], pw[r - l + 1]) + mod);
	}
};
