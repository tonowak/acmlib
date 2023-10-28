/*
 * Opis: Dodatek do generatorki
 */
mt19937 rng(random_device{}());
int rd(int l, int r) {
	return int(rng()%(r-l+1)+l);
}
