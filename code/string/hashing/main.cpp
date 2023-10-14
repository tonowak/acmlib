/*
 * Opis: Hashowanie z małą stałą. Można zmienić bazę (jeśli serio trzeba).
 */
struct Hashing {
	vector<LL> ha, pw;
	static constexpr LL mod = (1ll << 61) - 1;
	LL mul(LL a, LL b) {
		const auto c = __int128(a) * b;
		LL val = LL(c & mod) + LL(c >> 61);
		if (val >= mod) val -= mod;
		return val;
	}
	Hashing(const vector<int> &str, const int base = 37) {
		int len = ssize(str);
		ha.resize(len + 1);
		pw.resize(len + 1, 1);
		REP(i, len) {
			LL val = mul(ha[i], base) + str[i] + 1;
			if (val >= mod) val -= mod;
			ha[i + 1] = val;
			pw[i + 1] = mul(pw[i], base);
		}
	}
	LL operator()(int l, int r) {
		LL val = ha[r + 1] - mul(ha[l], pw[r - l + 1]) + mod;
		if (val >= mod) val -= mod;
		return val;
	}
};
