
/*
 * Opis: Struktura do działań modulo
 * Czas: O(1), dzielenie O(\log mod)
 * Użycie: Ustaw modulo w ostatniej linii. Jeśli modulo nie jest const, usuń pierwszy wiersz i zadeklaruj mod
 */

template<int mod>
struct mi {
	int val;
	mi() { val = 0; }
	mi(const LL& v) {
		val = (-mod <= v && v <= mod) ? v : v % mod;
		if(val < 0) val += mod;
	}

	friend ostream& operator<<(ostream &os, const mi &a) {
		return os << a.val;
	}
	friend istream& operator>>(istream &is, mi &a) {
		return is >> a.val;
	}

	friend bool operator==(const mi &a, const mi &b) {
		return a.val == b.val;
	}
	friend bool operator!=(const mi &a, const mi &b) {
		return !(a == b);
	}
	friend bool operator<(const mi &a, const mi &b) {
		return a.val < b.val;
	}
	friend bool operator<=(const mi &a, const mi &b) {
		return a.val <= b.val;
	}

	mi operator-() const { return mi(-val); }
	mi& operator+=(const mi &m) {
		if((val += m.val) >= mod) val -= mod;
		return *this;
	}
	mi& operator-=(const mi &m) {
		if((val -= m.val) < 0) val += mod;
		return *this;
	}
	mi& operator*=(const mi &m) {
		val = (LL) val * m.val % mod;
		return *this;
	}
	friend mi qpow(mi a, LL n) {
		if(n == 0) return 1;
		if(n % 2 == 1) return qpow(a, n - 1) * a;
		return qpow(a * a, n / 2);
	}
	friend mi inv(const mi &a) {
		assert(a != 0); return qpow(a, mod - 2);
	}
	mi& operator /=(const mi &m) { 
		return (*this) *= inv(m); 
	}

	friend mi operator+(mi a, const mi &b) { return a += b; }
	friend mi operator-(mi a, const mi &b) { return a -= b; }
	friend mi operator*(mi a, const mi &b) { return a *= b; }
	friend mi operator/(mi a, const mi &b) { return a /= b; }
};
using MI = mi<int(1e9 + 7)>;
