/**
 * Description: jakiś tam opis, można walnąć latexa: $2+2=5$. ęóąśłżźćńĘÓĄŚŁŻŹĆŃ
 * Time: O(n \sqrt{n} \log^2 n), gdzie $n$ to jakaś fajna zmienna
 * Memory: O(n \log n)
 * Status: untested / test.cpp / tested on codeforces/174D / not finished
 * Usage:
 *  int rd = getRandomValue(0, 5);
 *  int rd01 = ExampleStruct().get();
 *  ęóąśłżźćńĘÓĄŚŁŻŹĆŃ
 */

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

int getRandomValue(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

struct ExampleStruct {
	int random_variable;
	constexpr int left = 0, right = 1;

	ExampleStruct() {
		random_variable = getRandomValue(left, right);
		if(random_variable == 0) {
			// some random bulls**t to show the style
			++random_variable;
		}
		else
			--random_variable;
	}

	int& get_value() {
		return random_variable;
	}
};
