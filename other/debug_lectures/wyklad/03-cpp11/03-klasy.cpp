struct Struktura {
	int a, b;
	string c;

	void dodaj27() {
		a += 27;
		b += 27;
	}

	void ustaw(string s) {
		c = s + " xd";
	}
};

void func() {
	Struktura str;
	str.a = 42;
	str.b = 10;
	str.dodaj27();
	str.ustaw("abc");
}

/////

struct Struktura {
	int a = 4;
};
Struktura;

/////

struct Struktura {
	int a;
	Struktura(int x) {
		a = x;
	}
};
Struktura(4);

/////

struct Struktura {
	int a;
	Struktura(int x = 4) {
		a = x;
	}
};

/////

struct Struktura {
	Struktura() {
		cout << "konstruktor" << endl;
	}
	~Struktura() {
		cout << "destruktor" << endl;
	}
};

void func() {
	Struktura s;
	cout << "xd" << endl;
}

/////

vector<int> vec(a.begin(), a.end());
vector<int> vec;
vector<int> vec(n);
vector<int> vec(n, x);
cout << vec.size() << endl;
vec.clear();
