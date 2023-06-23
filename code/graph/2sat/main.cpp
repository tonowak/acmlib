/*
 * Opis: Zwraca poprawne przyporządkowanie zmiennym logicznym dla problemu 2-SAT, albo mówi, że takie nie istnieje
 * Użycie:
 *  TwoSat ts(ilość zmiennych);
 *  \~ oznacza negację
 *  ts.either(0, \sim3); // var 0 is true or var 3 is false
 *  ts.set_value(2); // var 2 is true
 *  ts.at_most_one({0,\sim1,2}); // co najwyżej jedna z var 0, \sim1 i  2 to prawda
 *  ts.solve(); // rozwiązuje i zwraca true jeśli rozwiązanie istnieje
 *  ts.values[0..N-1] // to wartości rozwiązania
 * Czas: O(n+m), gdzie n to ilość zmiennych, i m to ilość przyporządkowań.
 */

struct TwoSat {
	int n;
	vector<vector<int>> gr;
	vector<int> values;

	TwoSat(int _n = 0) : n(_n), gr(2 * n) {}

	void either(int f, int j) {
		f = max(2 * f, -1 - 2 * f);
		j = max(2 * j, -1 - 2 * j);
		gr[f].emplace_back(j ^ 1);
		gr[j].emplace_back(f ^ 1);
	}
	void set_value(int x) { either(x, x); }
	void implication(int f, int j) { either(~f, j); }

	int add_var() {
		gr.emplace_back();
		gr.emplace_back();
		return n++;
	}

	void at_most_one(vector<int>& li) {
		if(ssize(li) <= 1) return;
		int cur = ~li[0];
		FOR(i, 2, ssize(li) - 1) {
			int next = add_var();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}

	vector<int> val, comp, z;
	int t = 0;
	int dfs(int i) {
		int low = val[i] = ++t, x; 
		z.emplace_back(i);
		for(auto &e : gr[i]) if(!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if(low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x >> 1] == -1)
				values[x >> 1] = x & 1;
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(n, -1);
		val.assign(2 * n, 0);
		comp = val;
		REP(i, 2 * n) if(!comp[i]) dfs(i);
		REP(i, n) if(comp[2 * i] == comp[2 * i + 1]) return 0;
		return 1;
	}
};
