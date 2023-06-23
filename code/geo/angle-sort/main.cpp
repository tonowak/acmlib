/*
 * Opis: Sortowanie kątowe wektorów
 * Czas: O(n \log n)
 * Użycie:
 * Zwraca wektory P posortowane kątowo zgodnie z ruchem wskazówek zegara
 * od najbliższego kątowo do wektora (0, 1) włącznie.
 */
#include "../point/main.cpp"

bool cmp(P a, P b) {
	return cross(a, b) < 0;
}

vector<P> angle_sort(vector<P> t) {
	vector<P> pos, neg;
	for (P i : t) {
		if (i < P(0, 0))
			neg.emplace_back(i);
		else
			pos.emplace_back(i);
	}
	sort(pos.begin(), pos.end(), cmp);
	sort(neg.begin(), neg.end(), cmp);
	pos.insert(pos.end(), neg.begin(), neg.end());
	return pos;
}
