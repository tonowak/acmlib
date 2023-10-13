/*
 * Opis: O(n \log n),
 * zwraca wektory P posortowane kątowo zgodnie z ruchem wskazówek zegara
 * od najbliższego kątowo do wektora (0, 1) włącznie.
 * Aby posortować po argumencie (kącie) swapujemy x, y,
 * używamy angle-sort i ponownie swapujemy x, y.
 * Zakłada że nie ma punktu (0, 0) na wejściu.
 */
#include "../point/main.cpp"
vector<P> angle_sort(vector<P> t) {
	for(P p : t) assert(not equal(p, P(0, 0)));
	auto it = partition(t.begin(), t.end(), [](P a){ return P(0, 0) < a; });
	auto cmp = [&](P a, P b) {
		return sign(cross(a, b)) == -1;
	};
	sort(t.begin(), it, cmp);
	sort(it, t.end(), cmp);
	return t;
}
