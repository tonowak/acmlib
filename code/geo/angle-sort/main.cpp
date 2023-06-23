/*
 * Opis: Sortowanie kątowe wektorów
 * Czas: O(n \log n)
 * Użycie:
 * Zwraca wektory P posortowane kątowo zgodnie z ruchem wskazówek zegara
 * od najbliższego kątowo do wektora (0, 1) włącznie.
 * Aby posortować po argumencie (kącie) swapujemy x, y,
 * używamy angle-sort i ponownie swapujemy x, y.
 */
#include "../point/main.cpp"

vector<P> angle_sort(vector<P> t) {
	vector<P> pos, neg;
	for (P i : t) {
		if (i < P(0, 0))
			neg.emplace_back(i);
		else
			pos.emplace_back(i);
	}
	
	auto cmp = [&](P a, P b) {
		return cross(a, b) < 0;
	};

	sort(pos.begin(), pos.end(), cmp);
	sort(neg.begin(), neg.end(), cmp);
	pos.insert(pos.end(), neg.begin(), neg.end());
	return pos;
}
