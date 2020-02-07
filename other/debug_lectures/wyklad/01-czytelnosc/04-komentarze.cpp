// Krzysztof Małysa

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,n) for (int i = (a), i##__ = (n); i <= i##__; ++i)
#define FORD(i,a,n) for (int i = (a), i##__ = (n); i >= i##__; --i)
#define REP(i,n) FOR (i,0,n-1)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define EB emplace_back
#define ST first
#define ND second
#define OO(pp) template<class... A> inline ostream& operator<<(ostream& os, const pp<A...>& x) { return __o(os, ALL(x)); }

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII> VPII;

template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p);
template<class I> ostream& __o(ostream& os, I a, I b);
OO(vector)OO(deque)OO(map)OO(set)OO(multiset)OO(multimap)
template<class I> ostream& __o(ostream& os, I a, I b) {
	os << "{";
	while (a != b)
		os << *a, os << (++a == b ? "" : " ");
	return os << "}";
}
template<class I> ostream& __d(ostream& os, I a, I b) {
	os << "{\n";
	for (I c = a; a != b; ++a)
		os << "   " << distance(c, a) << ": " << *a << '\n';
	return os << "}";
}
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) {
	return os << '(' << p.ST << ' ' << p.ND << ')';
}
template<class A, class B> void mini(A& a, B&& b) { if (b < a) a = b; }
template<class A, class B> void maxi(A& a, B&& b) { if (b > a) a = b; }
int ceil2(int x) { return x < 2 ? 1 : 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }

#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define LOGN(...) D(cerr << #__VA_ARGS__ ": " << __VA_ARGS__ << '\n')
#define DUMP(...) D(cerr << #__VA_ARGS__ ": ", __d(cerr, ALL(__VA_ARGS__)) << '\n')
#define endl nl
constexpr char nl = '\n';
///////////////////////////////////////////////////////////////

int getint() {
	char c;
	do { c = _IO_getc_unlocked(stdin); } while (isspace(c));
	int x = c - '0';
	while (isdigit(c = _IO_peekc_unlocked(stdin))) {
		x = x * 10 + (c - '0');
		_IO_getc_unlocked(stdin);
	}
	return x;
}

// Used to build the graph
struct event1 {
	int x, y;
	int id;
	bool on_left;
};

bool operator<(const event1& a, const event1& b) { return (a.x == b.x ? a.y < b.y : a.x < b.x); }

ostream& operator<<(ostream& os, const event1& e) {
	return os << "(" << e.x << ' ' << e.y << "; " << e.id << ' ' << "RL"[e.on_left] << ")";
}

// Used to manage the unsafe points
struct event2 {
	int x;
	PII y; // if ST == ND then it is an unsafe point, otherwise it is a rectangle
	int id;
};

bool operator<(const event2& a, const event2& b) { return a.x < b.x; }

ostream& operator<<(ostream& os, const event2& e) {
	return os << "(" << e.x << ' ' << e.y << ' ' << e.id << ")";
}

class SegTree {
	int size;
	VI t;

	void propagate(int i) {
		if (t[i] != -1) {
			t[i << 1] = t[(i << 1) | 1] = t[i];
			t[i] = -1;
		}
	}

	int get(int a, int i, int sz) {
		if (sz == 1)
			return t[i];

		propagate(i);
		int sz2 = sz >> 1;
		if (a < sz2)
			return get(a, i << 1, sz2);
		else
			return get(a - sz2, (i << 1) | 1, sz2);
	}

	void set(int a, int b, int i, int sz, int x) {
		if (a == 0 && b == sz - 1) {
			t[i] = x;
			return;
		}

		propagate(i);
		int sz2 = sz >> 1;
		if (b < sz2)
			set(a, b, i << 1, sz2, x);
		else if (a >= sz2)
			set(a - sz2, b - sz2, (i << 1) | 1, sz2, x);
		else {
			set(a, sz2 - 1, i << 1, sz2, x);
			set(0, b - sz2, (i << 1) | 1, sz2, x);
		}
	}

public:
	SegTree(int n) : size(ceil2(n)), t(size << 1, -1) {}

	int get(int a) { return get(a, 1, size); }

	void set(int a, int b, int x) { set(a, b, 1, size, x); }
};

int main () {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int w, h, n, m;
	//cin >> w >> h >> n >> m;
	w = getint(), h = getint(), n = getint(), m = getint();

	PII p, s;
	//cin >> p.ST >> p.ND >> s.ST >> s.ND;
	p.ST = getint(), p.ND = getint(), s.ST = getint(), s.ND = getint();

	int pid = -1, sid = -1;
	vector<event1> ver, hor; // sweeping: vertical, horizontal
	vector<event2> ev;
	REP (i, n) {
		int x[2], y[2];
		//cin >> x[0] >> y[0] >> x[1] >> y[1];
		x[0] = getint(), y[0] = getint(), x[1] = getint(), y[1] = getint();
		sort(x, x + 2);
		sort(y, y + 2);

		ver.EB(event1{x[0], y[0], i, false});
		ver.EB(event1{x[1], y[0], i, true});

		hor.EB(event1{y[0], x[0], i, false});
		hor.EB(event1{y[1], x[0], i, true});

		ev.EB(event2{x[0], {y[0], y[1]}, i});

		// Check if p or s is in this rectange
		if (x[0] <= p.ST && p.ST <= x[1] && y[0] <= p.ND && p.ND <= y[1])
			pid = i;
		if (x[0] <= s.ST && s.ST <= x[1] && y[0] <= s.ND && s.ND <= y[1])
			sid = i;
	}

	sort(ALL(ver));
	sort(ALL(hor));

	VVI G(n);
	// Build graph
	REP (lllll, 2) {
		DUMP(ver);
		REP (i, SZ(ver)) {
			int end = i;
			while (end < SZ(ver) - 1 && ver[end + 1].x == ver[i].x)
				++end;
			// [i, end] contains all the points with x equal to ver[i].x
			int left_id = -1, right_id = -1;
			FOR (j, i, end) {
				if (ver[j].on_left)
					left_id = ver[j].id;
				else
					right_id = ver[j].id;

				// We have two events with the same y (one must be on the left and the other on the right)
				if (j < end && ver[j + 1].y == ver[j].y)
					continue;
				
				// Add edge
				if (left_id >= 0 && right_id >= 0) {
					D(cerr << "Adding edge: " << left_id << " -- " << right_id << nl);
					G[left_id].EB(right_id);
					G[right_id].EB(left_id);
				}
			}

			i = end;
		}
		D(cerr << "hor" << nl);
		ver.swap(hor);
	}

	DUMP(G);
	LOGN(pid);
	LOGN(sid);


	VI d(n); // Distances from pid (0 - not visited, -1 - unsafe)
	// Manage unsafe points
	while (m--) {
		int x, y;
		//cin >> x >> y;
		x = getint(), y = getint();
		ev.EB(event2{x, {y, y}, -1});
	}

	sort(ALL(ev));
	DUMP(ev);

	VI scaler; // scale ys in ev
	for (auto&& e : ev) {
		scaler.EB(e.y.ST);
		scaler.EB(e.y.ND);
	}
	sort(ALL(scaler));
	scaler.erase(unique(ALL(scaler)), scaler.end());

	// Assign rectangles to the points
	SegTree tr(scaler.size());
	for (auto e : ev) {
		PII y = e.y;
		y.ST = lower_bound(ALL(scaler), y.ST) - scaler.begin();
		y.ND = lower_bound(ALL(scaler), y.ND) - scaler.begin();
		if (y.ST == y.ND)
			d[tr.get(y.ST)] = -1;
		else
			tr.set(y.ST, y.ND, e.id);
	}
	
	// BFS from pid
	deque<int> Q = {pid};
	d[pid] = 1;
	while (Q.size()) {
		int x = Q.front();
		Q.pop_front();
		int dx = d[x];
		for (int i : G[x])
			if (d[i] == 0)
				d[i] = dx + 1, Q.EB(i);
	}
	DUMP(d);

	cout << d[sid] << nl;
	return 0;
}
