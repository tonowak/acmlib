/*
 * Opis: Pole wielokąta, niekoniecznie wypukłego
 * Użycie: w vectorze muszą być wierzchołki zgodnie z kierunkiem ruchu zegara. Jeśli Double jest intem to może się psuć / 2. 
 * area(a, b, c) zwraca pole trójkąta o takich długościach boku
 */
#include "../point/main.cpp"
Double area(vector<P> pts) {
	int n = size(pts);
	Double ans = 0;
	REP(i, n) ans += cross(pts[i], pts[(i + 1) % n]);
	return ans / 2;
}
Double area(Double a, Double b, Double c) {
	Double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}
