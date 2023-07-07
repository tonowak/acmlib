/* 
 * Opis: Dla pierwszego $mod$ oraz $a \perp mod, k$ znajduje $b$ takie, że $b^k = a$ 
 * (pierwiastek k-tego stopnia z $a$). Jak zwróci -1 to nie istnieje.
 */

#include "../primitive-root/main.cpp"
#include "../discrete-log/main.cpp"

int discrete_root(int a, int k) {
	int g = primitive_root();
	int y = discrete_log(powi(g, k), a);
	if(y == -1)
		return -1;
	return powi(g, y);
}

