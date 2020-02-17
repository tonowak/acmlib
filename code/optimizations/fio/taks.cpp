#include<bits/stdc++.h>
using namespace std;
 
ostream& operator<<(ostream &out, string str) {
	for(char c : str) out << c;
	return out;
}
 
template<class L, class R> ostream& operator<<(ostream &out, pair<L, R> p) {
	return out << "(" << p.first << ", " << p.second << ")";
}
 
template<class T> auto operator<<(ostream &out, T a) -> decltype(a.begin(), out) {
	out << "{";
	for(auto it = a.begin(); it != a.end(); it = next(it))
		out << (it != a.begin() ? ", " : "") << *it;
	return out << "}";
}
 
void dump() { cerr << "\n"; }
template<class T, class... Ts> void dump(T a, Ts... x) {
	cerr << a << ", ";
	dump(x...);
}
 
#ifdef DEBUG
#  define debug(...) cerr << "[" #__VA_ARGS__ "]: ", dump(__VA_ARGS__)
#else
#  define debug(...) false
#endif
 
#define REP(i, n) for(int i = 0; i < n; i++)
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ST first
#define ND second
 
template<class T> int size(T && a) { return a.size(); }
 
using LL = long long;
using PII = pair<int, int>;

void fastin(int &n) {
	n = 0;
	int c = 0;
	while(c < '0') c = getchar_unlocked();
	while('0' <= c && c <= '9') {
		n = n * 10 + c - '0';
		c = getchar_unlocked();
	}
}

struct frac {
	int a, b;
	frac(int x, int y) {
		int g = gcd(x, y);
		a = x / g, b = y / g;
		if(b < 0) a *= -1, b *= -1;
	}
};

frac inf(1e9, 1), zero(1, 1e9);

ostream& operator<<(ostream &out, frac f) {
	return out << "(" << f.a << " / " << f.b << ")";
}

bool operator<(frac a, frac b) {
	return (LL) a.a * b.b < (LL) a.b * b.a;
}

vector<int> ord, c, s;

struct Node {
	int l, r;
	frac mn = zero, mx = inf;
	Node(int x = -1) : l(x), r(x) {}
};

Node operator+(Node a, Node b) {
	Node ret;
	ret.l = a.l, ret.r = b.r;
	ret.mn = max(a.mn, b.mn);
	ret.mx = min(a.mx, b.mx);
	int i = a.r, j = b.l;
	if(i == -1 || j == -1) return ret;
	if(s[i] == s[j]) {
		if(c[i] <= c[j]) return ret;
		else {
			ret.mx = zero;
			ret.mn = inf;
			return ret;
		}
	}
	if(c[i] == c[j]) {
		if(s[i] <= s[j]) return ret;
		else {
			ret.mx = zero;
			ret.mn = inf;
			return ret;
		}
	}

	frac x(s[j] - s[i], c[i] - c[j]);
	if(c[i] < c[j]) ret.mn = max(ret.mn, x);
	else ret.mx = min(ret.mx, x);
	return ret;
}

struct Tree {
	vector<Node> tree;
	int size = 1;

	Tree(vector<int> val) {
		int n = val.size();
		while(size < n) size *= 2;
		tree.resize(size * 2);
		REP(i, n) tree[i + size] = Node(val[i]);
		for(int i = size - 1; i >= 1; i--)
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}

	void update(int pos, int val) {
		tree[pos += size] = Node(val);
		while(pos /= 2) 
			tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	fastin(n);
	ord = c = s = vector<int>(n);
	REP(i, n) fastin(s[i]), fastin(c[i]);
	REP(i, n) fastin(ord[i]), ord[i]--;
	Tree tree(ord);

	auto ans = [&]() {
		Node &root = tree.tree[1];
		if(root.mx < root.mn) cout << "NIE\n";
		else cout << root.mn.a << "/" << root.mn.b << "\n";
	};

	ans();

	int q;
	fastin(q);
	REP(i, q) {
		int a, b;
		fastin(a), fastin(b);
		a--, b--;
		swap(ord[a], ord[b]);
		tree.update(a, ord[a]);
		tree.update(b, ord[b]);
		ans();
	}
}
