/*
 * Opis: Dodatek do generatorki
 */
mt19937 rng(random_device{}());
int rd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}
