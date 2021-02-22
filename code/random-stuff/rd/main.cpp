/*
 * Opis: proste deterministyczne rd()
 */
mt19937 my_rng(0);
int my_rd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(my_rng);
}
