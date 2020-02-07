#include <bits/stdc++.h> // Tomasz Nowak
using namespace std;     // XIII LO Szczecin

#define FOR(i, a, n) for(int i = (a); i <= (b); ++i)
#define REP(i, n) FOR(i, 0, (n) - 1)

template<class A, class B> ostream& operator<<(ostream &os, pair<A, B> x) {
	return os << '(' << x.first << ", " << x.second << ')';
}
template<class T> ostream& operator<<(ostream &os, vector<T> x) { // tylko na vectory
	os << '{';
	for(auto a = x.begin(); a != x.end(); ++a)
		os << *a << (a == prev(x.end()) ? "" : " ");
	return os << '}';
}

#ifdef DEBUG
# define D(a...) a
#else
# define D(a...)
#endif
#define LOG(a...) D(cerr << #a ": " << a << "  ");
#define LN(a...) D(cerr << #a ": " << a << endl);

// end of templates

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int i = -123;
	pair<int, int> p = {6, 9};
	vector<int> v = {1, 2, 3, 4};
	vector<vector<int>> vv = {
		{1, 2, 3},
		{4, 5},
		{}
	};
	LOG(i);
	LN(p);
	LOG(v);
}
