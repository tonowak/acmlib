/*
 * Opis: Podstawa wynosi $1e9$. Mnożenie, dzielenie, nwd oraz modulo jest kwadratowe,
 * wersje \texttt{operatorX(Num, int)} liniowe.
 * Podstawę można zmieniać (ma zachodzić \texttt{base == 10^digits\_per\_elem}).
 */
// BEGIN HASH
struct Num {
	static constexpr int digits_per_elem = 9, base = int(1e9);
	int sign = 0;
	vector<int> x;
	Num& shorten() {
		while(ssize(x) and x.back() == 0)
			x.pop_back();
		for(int a : x)
			assert(0 <= a and a < base);
		if(x.empty())
			sign = 0;
		return *this;
	}
	Num(string s) {
		sign = ssize(s) and s[0] == '-' ? s.erase(s.begin()), -1 : 1;
		for(int i = ssize(s); i > 0; i -= digits_per_elem)
			if(i < digits_per_elem)
				x.emplace_back(stoi(s.substr(0, i)));
			else
				x.emplace_back(stoi(s.substr(i - digits_per_elem, digits_per_elem)));
		shorten();
	}
	Num() {}
	Num(LL s) : Num(to_string(s)) {}
}; // END HASH
// BEGIN HASH
string to_string(const Num& n) {
	stringstream s;
	s << (n.sign == -1 ? "-" : "") << (ssize(n.x) ? n.x.back() : 0);
	for(int i = ssize(n.x) - 2; i >= 0; --i)
		s << setfill('0') << setw(n.digits_per_elem) << n.x[i];
	return s.str();
}
ostream& operator<<(ostream &o, const Num& n) {
	return o << to_string(n).c_str();
} // END HASH
// BEGIN HASH
auto operator<=>(const Num& a, const Num& b) {
	if(a.sign != b.sign or ssize(a.x) != ssize(b.x))
		return ssize(a.x) * a.sign <=> ssize(b.x) * b.sign;
	for(int i = ssize(a.x) - 1; i >= 0; --i)
		if(a.x[i] != b.x[i])
			return a.x[i] * a.sign <=> b.x[i] * b.sign;
	return strong_ordering::equal;
}
bool operator==(const Num& a, const Num& b) {
	return a.x == b.x and a.sign == b.sign;
} // END HASH
// BEGIN HASH
Num abs(Num n) { n.sign &= 1; return n; }
Num operator+(Num a, Num b) {
	int mode = a.sign * b.sign >= 0 ? a.sign |= b.sign, 1 : abs(b) > abs(a) ? swap(a, b), -1 : -1, carry = 0;
	for(int i = 0; i < max(ssize((mode == 1 ? a : b).x), ssize(b.x)) or carry; ++i) {
		if(mode == 1 and i == ssize(a.x))
			a.x.emplace_back(0);
		a.x[i] += mode * (carry + (i < ssize(b.x) ? b.x[i] : 0));
		carry = a.x[i] >= a.base or a.x[i] < 0;
		a.x[i] -= mode * carry * a.base;
	}
	return a.shorten();
} // END HASH
Num operator-(Num a) { a.sign *= -1; return a; }
Num operator-(Num a, Num b) { return a + -b; }
// BEGIN HASH
Num operator*(Num a, int b) {
	assert(abs(b) < a.base);
	int carry = 0;
	for(int i = 0; i < ssize(a.x) or carry; ++i) {
		if(i == ssize(a.x))
			a.x.emplace_back(0);
		LL cur = a.x[i] * LL(abs(b)) + carry;
		a.x[i] = int(cur % a.base);
		carry = int(cur / a.base);
	}
	if(b < 0)
		a.sign *= -1;
	return a.shorten();
} // END HASH
// BEGIN HASH
Num operator*(const Num& a, const Num& b) {
	Num c;
	c.x.resize(ssize(a.x) + ssize(b.x));
	REP(i, ssize(a.x))
		for(int j = 0, carry = 0; j < ssize(b.x) or carry; ++j) {
			LL cur = c.x[i + j] + a.x[i] * LL(j < ssize(b.x) ? b.x[j] : 0) + carry;
			c.x[i + j] = int(cur % a.base);
			carry = int(cur / a.base);
		}
	c.sign = a.sign * b.sign;
	return c.shorten();
} // END HASH
// BEGIN HASH
Num operator/(Num a, int b) {
	assert(b != 0 and abs(b) < a.base);
	int carry = 0;
	for(int i = ssize(a.x) - 1; i >= 0; --i) {
		LL cur = a.x[i] + carry * LL(a.base);
		a.x[i] = int(cur / abs(b));
		carry = int(cur % abs(b));
	}
	if(b < 0)
		a.sign *= -1;
	return a.shorten();
} // END HASH
// BEGIN HASH
// zwraca a * pow(a.base, b)
Num shift(Num a, int b) {
	vector v(b, 0);
	a.x.insert(a.x.begin(), v.begin(), v.end());
	return a.shorten();
}
Num operator/(Num a, Num b) {
	assert(ssize(b.x));
	int s = a.sign * b.sign;
	Num c;
	a = abs(a);
	b = abs(b);
	for(int i = ssize(a.x) - ssize(b.x); i >= 0; --i) {
		if (a < shift(b, i)) continue;
		int l = 0, r = a.base - 1;
		while (l < r) {
			int m = (l + r + 1) / 2;
			if (shift(b * m, i) <= a)
				l = m;
			else
				r = m - 1;
		}
		c = c + shift(l, i);
		a = a - shift(b * l, i);
	}
	c.sign = s;
	return c.shorten();
} // END HASH
// BEGIN HASH
template<typename T>
Num operator%(const Num& a, const T& b) { return a - ((a / b) * b); }
Num nwd(const Num& a, const Num& b) { return b == Num() ? a : nwd(b, a % b); }
// END HASH
