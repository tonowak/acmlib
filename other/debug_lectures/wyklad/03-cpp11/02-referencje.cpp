int &x = a;

/////

void f1() {
	int a = 42;

	int b = a;
	b += 27;
	cout << a << endl;

	int &c = a;
	c += 27;
	cout << a << endl;
}

/////

void dodaj27_1(int x) {
	x += 27;
}

void dodaj27_2(int &x) {
	x += 27;
}

int a = 42;
dodaj27_1(a);
dodaj27_2(a);
dodaj27_2(42); // why?

/////

vector<int> x(n); // O(n)

/////

int mediana(vector<int> x) {
	// zakładam, że długość vectora jest nieparzysta
	return x[int(x.size()) / 2];
}

int main() {
	vector<int> vec(n); // jakis n-elementowy vector
	sort(vec.begin(), vec.end());

	for(int i = 0; i < n; ++i)
		cout << vec[i] - mediana(vec) << endl;
}

/////

int &x;
x = a;

/////

int &x = a;
x = b;

/////

int &x = a, y = b, &z = c;

/////

int& dodaj_27(int x) {
	x += 27;
	return x;
}

int a = 42;
dodaj_27(a);
dodaj_27(a) += 1;

/////
