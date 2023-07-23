#include "../../utils/testing/test-wrapper.cpp"
#define CHANGABLE_MOD
#include "main.cpp"

void test() {
	static vector<int> mods = {2, 3, 5, 7, 11, 13, 17, int(1e9) + 7};
	mod = mods[rd(0, ssize(mods) - 1)];
	const int max_number_of_variables = 10;
	const int max_number_of_equations = 10;
	const int number_of_variables = rd(0, max_number_of_variables);
	const int number_of_equations = rd(1, max_number_of_equations);
	debug(mod, number_of_variables, number_of_equations);
	vector equations(number_of_equations, vector (number_of_variables + 1, 0));
	auto eval = [&](int id, const vector<int>& assignment) {
		int sum = 0;
		REP(j, number_of_variables)
			sum = add(sum, mul(equations[id][j], assignment[j]));
		return sum;
	};
	REP(i, number_of_equations) {
		REP(j, number_of_variables + 1)
			equations[i][j] = rd(0, mod - 1);
	}
	debug(equations);
	auto [ans, assignment] = gauss(equations);
	debug(ans, assignment);
	if (ans >= 1) {
		REP(i, number_of_equations)
			assert(eval(i, assignment) == equations[i][number_of_variables]);
	}
	if (pow(mod, number_of_variables) < 1e4) {
		debug("checked ans");
		int cnt = 0;
		vector<int> values(number_of_variables);
		function<void(int)> rec = [&](int pos) {
			if (pos == number_of_variables) {
				bool ok = true;
				REP(i, number_of_equations) {
					if (eval(i, values) != equations[i][number_of_variables]) {
						ok = false;
						break;
					}
				}
				cnt += ok;
				return;
			}
			REP(i, mod) {
				values[pos] = i;
				rec(pos + 1);
			}
		};
		rec(0);
		if (cnt > 1)
			cnt = 2;
		assert(cnt == ans);
	}
}
