/*
 * Opis: O(n \log n),
 * zwraca wektory P posortowane kątowo zgodnie z ruchem wskazówek zegara
 * od najbliższego kątowo do wektora (0, 1) włącznie.
 * Aby posortować po argumencie (kącie) swapujemy x, y,
 * używamy angle-sort i ponownie swapujemy x, y.
 */
#include "../point/main.cpp"

vector<P> angle_sort(vector<P> t) {
	auto it = partition(t.begin(), t.end(), [](P a){ return P(0, 0) < a; });
	auto cmp = [&](P a, P b) {
		return cross(a, b) < 0;
	};
	sort(t.begin(), it, cmp);
	sort(it, t.end(), cmp);
	return t;
}
