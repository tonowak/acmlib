#include <bits/stdc++.h> // Tomasz Nowak
using namespace std;     // XIII LO Szczecin

#define FOR(i,a,n) for (auto i = (a), i##__ = (n); i <= i##__; ++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define FORD(i,a,n) for (auto i = (a), i##__ = (n); i >= i##__; --i)
#define REPD(i,n) FORD(i,(n)-1,0)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int) x.size())
#define X first
#define Y second
#define V vector
#define A array
constexpr char nl = '\n';

template<class A, class B> A&& mini(A &&a, B &&b) { if (b < a) a = b; return a; }
template<class A, class B> A&& maxi(A &&a, B &&b) { if (b > a) a = b; return a; }
int first_bit(int x) { return x == 0 ? 0 : sizeof(x) * 8 - __builtin_clz(x); }
int ceil2(int x) { return x < 2 ? x : 1 << first_bit(x - 1); }
constexpr int inf = 0x3f3f3f3f; 
constexpr long long inf_l = 0x3f3f3f3f3f3f3f3f;

#define _eif(a...) typename enable_if<a, int>::type()
#define _func(func, a...) template<class T> auto func(T &&x) -> decltype(a)
#define _rref(a...) typename remove_reference<a>::type
#define _create_trait(name, a...) \
    _func(_##name, a, true_type{}); \
    false_type _##name(...); \
    template<class T> struct name : decltype(_##name(declval<T>())) {};
struct Debug;
_create_trait(is_debug_func, x(declval<add_lvalue_reference<Debug>::type>()));
_create_trait(is_func, x())
_create_trait(is_string, string(x))
_create_trait(is_ptr, *x, _eif(is_string<T>() == false));
_create_trait(is_container, x.begin(), _eif(is_string<T>() == false))

template<class Iter> struct Off { Iter _a, _b; };
_func(O, _eif(is_container<T>() == true), Off<decltype(x.begin())>()) { return { ALL(x) }; }
_func(O, _eif(is_container<T>() == false), x) { return x; }

#define _operator(a...) _func(operator<<, a, *this)
struct Debug {
    Debug() {  cerr << boolalpha; }
    ~Debug() { cerr << nl; }
    Debug& operator()(int x = 1) { REP(_, x) *this << "  "; return *this; }
    _operator(cerr << x, _eif(is_func<T>() == false && is_ptr<T>() == false && is_integral<_rref(T)>() == true)) { 
        using L = long long;
        if(abs(int(x)) == inf || abs(L(x)) == inf_l)
            cerr << ((int(x) == inf || L(x) == inf_l) ? "+∞" : (int(x) == -inf || L(x) == -inf_l) ? "-∞" : "?");
        else
            cerr << x;
        return *this; 
    }
    _operator(cerr << x, _eif(is_func<T>() == false && is_ptr<T>() == false && is_integral<_rref(T)>() == false)) {
        cerr << x;
        return *this;
    }
    _operator(x.first) { 
        return *this << "(" << O(x.first) << ", " << O(x.second) << ")"; }
    _operator(_eif(is_container<T>() == true)) {
        *this << "{\n";
        for (auto a = x.begin(); a != x.end(); ++a)
            *this << "  " << distance(x.begin(), a) << ": " << O(*a) << '\n';
        return *this << "}";
    }
    _operator(x._a) {
        *this << "{";
        for (auto a = x._a, b = x._b; a != b; ++a)
            *this << O(*a) << (next(a) == b ? "" : ", ");
        return *this << "}";
    }
    _operator(_eif(is_func<T>() == true)) { x(); return *this; }
    _operator(_eif(is_debug_func<T>() == true)) { x(*this); return *this; }
    _operator(_eif(is_ptr<T>() == true && is_func<T>() == false && is_debug_func<T>() == false)) {
        return *this << *x;
    }
};
struct DebugOff { 
    template<class T> DebugOff& operator<<(T&&) { return *this; }
    DebugOff& operator()(int = 0) { return *this; }
};

#ifdef DEBUG
# define D Debug()
#else
# define D DebugOff()
#endif
#define I(a...) #a ": " << a << "   "

using VI    = V<int>;
using VVI   = V<VI>;
using L     = long long;
using VL    = V<L>;
using VB    = V<bool>;
using II    = pair<int, int>;
using VII   = V<II>;
using VVII  = V<VII>;

// end of templates v8 by Tomasz Nowak

struct Pomiar {
	int l, r;
	vector<int> x;
	vector<II> segments;
	void operator()(Debug &d) {
		d << II(l, r) << ": " << O(x) << ", seg: " << O(segments);
	}
};

struct Tree {
	int sz;
	VII t;

	II& better(II &l, II &r) {
		if(l.X >= r.X)
			return l;
		else
			return r;
	}

	Tree(int n) : sz(ceil2(n)), t(2 * sz, II(inf, -1)) {
		REP(v, sz)
			t[v + sz].Y = v;
		REPD(v, sz)
			t[v] = better(t[v << 1], t[v << 1 | 1]);
	}

	II get(int l, int r) {
		II answer = better(t[l += sz], t[r += sz]);
		while((l >> 1) != (r >> 1)) {
			if(~l & 1)
				answer = better(answer, t[l ^ 1]);
			if(r & 1)
				answer = better(answer, t[r ^ 1]);
			l >>= 1;
			r >>= 1;
		}
		return answer;
	}

	void set(int pos, int val) {
		t[pos += sz].X = val;
		while(pos >>= 1)
			t[pos] = better(t[pos << 1], t[pos << 1 | 1]);
	}
};
			
vector<Pomiar> pomiary;
VVI pomiary_with;
VI value;
bool failed = false;
VB visited_pos, visited_pom;
Tree tree(0);

void DFS_pos(int);

void DFS_pomiar(int pom_i) {
	D << "correcting with " << I(pom_i);
	visited_pom[pom_i] = true;

	int mx = -inf;
	for(II seg : pomiary[pom_i].segments) {
		II x = tree.get(seg.X, seg.Y);
		while(x.X == inf) {
			DFS_pos(x.Y);
			D << "left recc";
			if(failed)
				return;
			x = tree.get(seg.X, seg.Y);
		}
		D << "for segment " << seg << " got " << x;
		maxi(mx, x.X);
	}

	D << "corrected " << pom_i << " to " << mx + 1;
	for(int x : pomiary[pom_i].x) {
		maxi(value[x], mx + 1);
	}
}

void DFS_pos(int pos) {
	D << "resolving " << I(pos);
	if(visited_pos[pos] == true) {
		failed = true;
		return;
	}
	visited_pos[pos] = true;

	while(SZ(pomiary_with[pos])) {
		if(failed)
			return;

		int pom = pomiary_with[pos].back();
		pomiary_with[pos].pop_back();
		if(visited_pom[pom] == false)
			DFS_pomiar(pom);
		// else
			// failed = true;
	}
	tree.set(pos, value[pos]);
	D << "set " << pos << " to " << value[pos];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, s, m;
	cin >> n >> s >> m;
	VI initial(n);
	REP(i, s) {
		int p, d;
		cin >> p >> d;
		initial[--p] = d;
	}
	pomiary.resize(m);
	for(Pomiar &p : pomiary) {
		int k;
		cin >> p.l >> p.r >> k;
		--p.l;
		--p.r;
		p.x.resize(k);
		for(int &a : p.x) {
			cin >> a;
			--a;
		}

		REP(i, k + 1) {
			int left = i ? p.x[i - 1] + 1 : p.l,
				right = i != k ? p.x[i] - 1 : p.r;
			if(left <= right)
				p.segments.emplace_back(left, right);
		}
	}
	D << I(n) << I(s) << I(m) << I(initial) << I(pomiary);

	pomiary_with.resize(n);
	REP(i, m)
		for(int x : pomiary[i].x)
			pomiary_with[x].emplace_back(i);
	D << I(O(pomiary_with));

	value = initial;
	REP(i, n)
		if(value[i] == 0 && SZ(pomiary_with[i]) == 0)
			value[i] = 1;

	tree = Tree(n);
	REP(i, n)
		if(value[i])
			tree.set(i, value[i]);
	// D << I(tree.t);

	REP(i, n)
		if(value[i] == 0)
			value[i] = 1;

	visited_pom.resize(m);
	visited_pos.resize(n);
	REP(i, n)
		if(initial[i] == 0 && visited_pos[i] == false)
			DFS_pos(i);
	D << I(failed) << I(value);

	bool valid = !failed;
	REP(i, n)
		if(initial[i] && initial[i] != value[i])
			valid = false;
		else if(value[i] > int(1e9))
			valid = false;

	auto check_validity = [&] {
		REP(i, n)
			if(tree.get(i, i).X != value[i])
				return false;
		for(Pomiar &p : pomiary) {
			int mx = 0;
			for(II seg : p.segments) {
				II x = tree.get(seg.X, seg.Y);
				maxi(mx, x.X);
			}
			for(int x : p.x)
				if(value[x] <= mx)
					return false;
		}
		return true;
	};

	if(valid && check_validity()) {
		D << I(tree.t);
		cout << "TAK" << nl;
		for(int i : value)
			cout << i << ' ';
	} else {
		cout << "NIE" << nl;
	}
}
