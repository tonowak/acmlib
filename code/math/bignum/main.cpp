/*
 * Opis: Podstawa wynosi $1e9$. Mnożenie, dzielenie, nwd oraz modulo jest kwadratowe,
 * wersje \texttt{operatorX(Num, int)} liniowe.
 * Podstawę można zmieniać (ma zachodzić \texttt{base == 10 do digits\_per\_elem}).
 */
// BEGIN HASH
struct Num {
	static constexpr int digits_per_elem = 9, base = int(1e9);
	vector<int> x;
	Num& shorten() {
		while(ssize(x) and x.back() == 0)
			x.pop_back();
		for(int a : x)
			assert(0 <= a and a < base);
		return *this;
	}
	Num(const string& s) {
		for(int i = ssize(s); i > 0; i -= digits_per_elem)
			if(i < digits_per_elem)
				x.emplace_back(stoi(s.substr(0, i)));
			else
				x.emplace_back(stoi(s.substr(i - digits_per_elem, digits_per_elem)));
		shorten();
	}
	Num() {}
	Num(LL s) : Num(to_string(s)) {
		assert(s >= 0);
	}
}; // END HASH
// BEGIN HASH
string to_string(const Num& n) {
	stringstream s;
	s << (ssize(n.x) ? n.x.back() : 0);
	for(int i = ssize(n.x) - 2; i >= 0; --i)
		s << setfill('0') << setw(n.digits_per_elem) << n.x[i];
	return s.str();
}
ostream& operator<<(ostream &o, const Num& n) {
	return o << to_string(n).c_str();
} // END HASH
// BEGIN HASH
Num operator+(Num a, const Num& b) {
	int carry = 0;
	for(int i = 0; i < max(ssize(a.x), ssize(b.x)) or carry; ++i) {
		if(i == ssize(a.x))
			a.x.emplace_back(0);
		a.x[i] += carry + (i < ssize(b.x) ? b.x[i] : 0);
		carry = bool(a.x[i] >= a.base);
		if(carry)
			a.x[i] -= a.base;
	}
	return a.shorten();
} // END HASH
// BEGIN HASH
bool operator<(const Num& a, const Num& b) {
	if(ssize(a.x) != ssize(b.x))
		return ssize(a.x) < ssize(b.x);
	for(int i = ssize(a.x) - 1; i >= 0; --i)
		if(a.x[i] != b.x[i])
			return a.x[i] < b.x[i];
	return false;
}
bool operator==(const Num& a, const Num& b) {
	return a.x == b.x;
}
bool operator<=(const Num& a, const Num& b) {
	return a < b or a == b;
} // END HASH
// BEGIN HASH
Num operator-(Num a, const Num& b) {
	assert(b <= a);
	int carry = 0;
	for(int i = 0; i < ssize(b.x) or carry; ++i) {
		a.x[i] -= carry + (i < ssize(b.x) ? b.x[i] : 0);
		carry = a.x[i] < 0;
		if(carry)
			a.x[i] += a.base;
	}
	return a.shorten();
} // END HASH
// BEGIN HASH
Num operator*(Num a, int b) {
	assert(0 <= b and b < a.base);
	int carry = 0;
	for(int i = 0; i < ssize(a.x) or carry; ++i) {
		if(i == ssize(a.x))
			a.x.emplace_back(0);
		LL cur = a.x[i] * LL(b) + carry;
		a.x[i] = int(cur % a.base);
		carry = int(cur / a.base);
	}
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
	return c.shorten();
} // END HASH
// BEGIN HASH
Num operator/(Num a, int b) {
	assert(0 < b and b < a.base);
	int carry = 0;
	for(int i = ssize(a.x) - 1; i >= 0; --i) {
		LL cur = a.x[i] + carry * LL(a.base);
		a.x[i] = int(cur / b);
		carry = int(cur % b);
	}
	return a.shorten();
} // END HASH
// BEGIN HASH
// zwraca a * pow(a.base, b)
Num shift(Num a, int b) {
	vector v(b, 0);
	a.x.insert(a.x.begin(), v.begin(), v.end());
	return a.shorten();
}
Num operator/(Num a, const Num& b) {
	assert(ssize(b.x));
	Num c;
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
	return c.shorten();
} // END HASH
// BEGIN HASH
template<typename T>
Num operator%(const Num& a, const T& b) {
	return a - ((a / b) * b);
}
Num nwd(const Num& a, const Num& b) {
	if(b == Num())
		return a;
	return nwd(b, a % b);
} // END HASH
