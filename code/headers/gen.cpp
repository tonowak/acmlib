/*
 * Opis: Dodatek do generatorki
 */
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
int rd(int l, int r) {
	return int(rng()%(r-l+1)+l);
}
