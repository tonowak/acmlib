#include "../headers/main.cpp"

void test();

mt19937 rng(0);
int rd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}
LL rd_ll(LL l, LL r) {
	return uniform_int_distribution<LL>(l, r)(rng);
}

template<class T>
int difference(T &start, T &end) {
	return int(chrono::duration_cast<chrono::milliseconds>(end - start).count());
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		cerr << "The only accepted argument is time in seconds\n";
		return 1;
	}

	int milli_limit = 1000 * atoi(argv[1]);
	auto start_time = chrono::steady_clock::now();
	auto last_measured = start_time;

	int test_no = 0;

	while(difference(start_time, last_measured) < milli_limit) {
		try {
			test();
		}
		catch(const exception &e) {
            cout << "WA\n";
			return 1;
		}
		auto curr = chrono::steady_clock::now();
		++test_no;
		last_measured = curr;
	}
    cout << "OK (tests passed: " << test_no << ")\n";
}

