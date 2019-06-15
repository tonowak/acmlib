#include <bits/stdc++.h>
using namespace std;

bool test(int milliseconds);

template<class T>
int difference(T &start, T &end) {
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
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
		int remaining_milli = milli_limit - difference(start_time, last_measured);
		if(test(remaining_milli)) {
			cout << "WA: " << test_no << '\n';
			return 0;
		}
		auto curr = chrono::steady_clock::now();
		int elapsed = difference(last_measured, curr);
		cout << "OK: " << test_no++ << " (" << double(elapsed) / 1000 << " s)\n";
		last_measured = curr;
	}
}

