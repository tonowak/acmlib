//wczytywanie / wypluwanie
#include <iostream>
//#include <cstdio>

//kontenery
#include <vector>
//#include <map>
//#include <queue>
//#include <stack>

//reszta
//#include <string>
#include <algorithm>
//#include <cmath>

using namespace std;

typedef vector<int> vi;

vi waga;
int n;

void przygotuj()
{
	waga.resize(n);
}

void wczytajDane()
{
	for (int i = 0; i != n; ++i)
	{
		cin >> waga[i];
	}
}

int pozycjaNajwiekszejNaPrzedziale(int a, int b)
{
	int najwieksza = 0, iNajwiekszej = 0;
	for (int i = a; i != b + 1; ++i)
	{
		if (waga[i] > najwieksza)
		{
			iNajwiekszej = i;
			najwieksza = waga[i];
		}
	}
	return iNajwiekszej;
}

int najmniejszaIloscPrzewrocenNaPrzedziale(int a, int b)
{
	int i = pozycjaNajwiekszejNaPrzedziale(a, b);
	if (i == a || i == b)
		return 1;
	return min(najmniejszaIloscPrzewrocenNaPrzedziale(a, i - 1), najmniejszaIloscPrzewrocenNaPrzedziale(i + 1, b)) + 1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	przygotuj();
	wczytajDane();
	cout << najmniejszaIloscPrzewrocenNaPrzedziale(0, n - 1);

	//system("pause"); //zakomentowac przy wrzucaniu na sprawdzarke
	return 0;
}
