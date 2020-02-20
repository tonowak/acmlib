#include "../../utils/headers/main.cpp"
#include "main.cpp"

vector<int> gen_prime(int n) {
	vector<bool> sitko(n + 1, false);
	vector<int> ret;
	for(int i = 2; i <= n; i++) {
		if(!sitko[i]) {
			ret.emplace_back(i);
			for(int j = i * 2; j <= n; j += i)
				sitko[j] = true;
		}
	}
}

int main() {
	int n;
	cin >> n;
	sieve(n);
	assert(prime == gen_prime(n));
	cerr << "OK\n";
}
