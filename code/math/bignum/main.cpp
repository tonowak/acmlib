/*
 * Opis: Reprezentacja dużych int'ów
 * Status: Przetestowane na jednym zadaniu xd
 * Czas: Podstawa 1e9, mnożenie kwadratowe, dzielenie to mnożenie z logiem
 * Użycie:
 *   cout << Num("123") % Num("32")
 */

struct Num {
	static constexpr int digits_per_elem = 9, base = int(1e9);
	vector<int> x;

	Num& shorten() {
		while(ssize(x) and x.back() == 0)
			x.pop_back();
		for(int &a : x)
			assert(0 <= a and a < base);
		return *this;
	}

	Num(string s) {
		for(int i = ssize(s); i > 0; i -= digits_per_elem)
			if(i < digits_per_elem)
				x.emplace_back(stoi(s.substr(0, i)));
			else
				x.emplace_back(stoi(s.substr(i - digits_per_elem, 9)));
		shorten();
	}
	Num() {}
};

string to_string(Num n) {
	stringstream s;
	s << (ssize(n.x) ? n.x.back() : 0);
	for(int i = ssize(n.x) - 2; i >= 0; --i)
		s << setfill('0') << setw(n.digits_per_elem) << n.x[i];
	return s.str();
}
ostream& operator<<(ostream &o, Num n) {
	return o << to_string(n).c_str();
}

Num operator+(Num a, Num b) {
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
}

bool operator<(Num a, Num b) {
	if(ssize(a.x) != ssize(b.x))
		return ssize(a.x) < ssize(b.x);
	for(int i = ssize(a.x) - 1; i >= 0; --i)
		if(a.x[i] != b.x[i])
			return a.x[i] < b.x[i];
	return false;
}
bool operator==(Num a, Num b) {
	return a.x == b.x;
}
bool operator<=(Num a, Num b) {
	return a < b or a == b;
}

Num operator-(Num a, Num b) {
	assert(b <= a);
	int carry = 0;
	for(int i = 0; i < ssize(b.x) or carry; ++i) {
		a.x[i] -= carry + (i < ssize(b.x) ? b.x[i] : 0);
		carry = a.x[i] < 0;
		if(carry)
			a.x[i] += a.base;
	}
	return a.shorten();
}

Num operator*(Num a, Num b) {
	Num c;
	c.x.resize(ssize(a.x) + ssize(b.x));
	REP(i, ssize(a.x))
		for(int j = 0, carry = 0; j < ssize(b.x) || carry; ++j) {
			LL cur = c.x[i + j] + a.x[i] * 1ll * (j < ssize(b.x) ? b.x[j] : 0) + carry;
			c.x[i + j] = int(cur % a.base);
			carry = int(cur / a.base);
		}
	return c.shorten();
}

Num operator/(Num a, int b) {
	assert(0 < b and b < a.base);
	int carry = 0;
	for(int i = ssize(a.x) - 1; i >= 0; --i) {
		LL cur = a.x[i] + carry * LL(a.base);
		a.x[i] = int(cur / b);
		carry = int(cur % b);
	}
	return a.shorten();
}

Num operator/(Num a, Num b) {
	Num l = Num(), r = a;
	while(not (l == r)) {
		Num m = (l + r + Num("1")) / 2;
		if(m * b <= a)
			l = m;
		else
			r = m - Num("1");
	}
	// assert(mul(l, b) == a);
	return l.shorten();
}

Num operator%(Num a, Num b) {
	Num d = a / b;
	return a - ((a / b) * b);
}

Num nwd(Num a, Num b) {
	if(b == Num())
		return a;
	return nwd(b, a % b);
}
