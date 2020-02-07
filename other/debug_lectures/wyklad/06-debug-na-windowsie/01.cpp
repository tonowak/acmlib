// zadanie: największy spójny podciąg
#include <bits/stdc++.h>
using namespace std;

mt19937_64 _gen(chrono::system_clock::now().time_since_epoch().count()); // tasiemce, można też użyć rand() co zwraca zupełnie losową liczbę, nie pamiętam jak seedować, trzeba wygooglać
template<class T> T rd(T a, T b) { return uniform_int_distribution<T>(a, b)(_gen); }

struct Generatorka {
	int n;
	vector<int> a;

	Generatorka(int m, int zakres) {
		n = rd(1, m);
		a.resize(n);
		for(int &i : a)
			i = rd(-zakres, zakres);
	}
};

struct Brute {
	int odp = 0;

	Brute(int n, vector<int> a) {
		for(int l = 0; l < n; ++l)
			for(int r = l; r < n; ++r) {
				int suma = 0;
				for(int i = l; i <= r; ++i)
					suma += a[i];
				if(suma > odp)
					odp = suma;
			}
	}
};

struct Wzorcowka {
	int odp = 0;

	Wzorcowka(int n, vector<int> a) {

		vector<int> prefix(n);
		prefix[0] = a[0];
		for(int i = 1; i < n; ++i)
			prefix[i] = prefix[i - 1] + a[i];

		int min_pref = 0, best_sum = 0;
		for(int i = 0; i < n; ++i) {
			best_sum = prefix[i] - min_pref;
			if(best_sum > odp)
				odp = best_sum;
			if(prefix[i] < min_pref)
				min_pref = prefix[i];
		}
	}
};

bool dobra_odp(Brute &b, Wzorcowka &w) {
	return b.odp == w.odp;
}

int main() {
	int test_nr = 0;
	while(true) {
		Generatorka g(100, 1000);
		Brute b(g.n, g.a);
		Wzorcowka w(g.n, g.a);

		if(dobra_odp(b, w) == false) {
			cout << g.n << endl;
			for(int a : g.a)
				cout << a << ' ';
			cout << endl << "brute: " << b.odp << endl << "wzorc: " << w.odp << endl;

			break;
		}
		cout << "OK " << ++test_nr << endl;
	}
}

