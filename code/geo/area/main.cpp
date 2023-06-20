/*
 * Opis: Pole wielokąta, niekoniecznie wypukłego
 * Użycie: w vectorze muszą być wierzchołki zgodnie z kierunkiem ruchu zegara. Jeśli D jest intem to może się psuć / 2.
 * area(a, b, c) zwraca pole trójkąta o takich długościach boku
 */
#include "../point/main.cpp"
D area(vector<P> pts) {
	int n = size(pts);
	D ans = 0;
	REP(i, n) ans += cross(pts[i], pts[(i + 1) % n]);
	return fabsl(ans / 2);
}
D area(D a, D b, D c) {
	D p = (a + b + c) / 2;
	return sqrtl(p * (p - a) * (p - b) * (p - c));
}
