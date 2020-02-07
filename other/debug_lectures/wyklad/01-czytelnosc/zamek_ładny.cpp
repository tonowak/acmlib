#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,n) for (auto i = (a), i##__ = (n); i <= i##__; ++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define FORD(i,a,n) for (auto i = (a), i##__ = (n); i >= i##__; --i)
#define REPD(i,n) FORD(i,(n)-1,0)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int) x.size())
#define EB emplace_back
#define RS resize
#define ST first
#define ND second
#define V vector

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
using VLL   = V<pair <L, L> >;
using LL    = pair<L, L>;
using II    = pair<int, int>;
using A4    = array<int, 4>;
// end of templates
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d, X, Y;
    int xp, yp, xs, ys;
    cin >> X >> Y >> n >> d;
    cin >> xp >> yp >> xs >> ys;

    V< array<int, 4> > Wsp(n + 1);
    VVI List(n + 1);
    VI Vis(n + 1);
 
    if(X <= 2000 && Y <= 2000)
    {
        A4 A = {{-1, -1, -1, -1}};
        V <A4> B;
        B.RS(Y + 1, A);
        V < V <A4> > Czyje;
        Czyje.RS(X + 1, B);

        REP(i, n)
        {
            cin >> Wsp[i][0] >> Wsp[i][1] >> Wsp[i][2] >> Wsp[i][3];
            if(Wsp[i][0] > Wsp[i][2]) 
                swap(Wsp[i][0], Wsp[i][2]);
            if(Wsp[i][1] > Wsp[i][3]) 
                swap(Wsp[i][1], Wsp[i][3]);
 
            FOR(j, Wsp[i][0], Wsp[i][2])
                FOR(h, Wsp[i][1], Wsp[i][3])
                    REP(k, 3)
                    {
                        if(Czyje[j][h][k] == -1)
                        {
                            Czyje[j][h][k] = i;
                            break;
                        }
                        else
                        {
                            if((j == Wsp[i][0] || j == Wsp[i][2]) && (h == Wsp[i][1] || h == Wsp[i][3])) /// mamy do czynienia z wierzcholkiem
                            {
                                bool xd = 1;
                                if(Wsp[i][0] == Wsp[Czyje[j][h][k]][2] && Wsp[i][1] == Wsp[Czyje[j][h][k]][3])
                                    xd = 0;
                                if(Wsp[i][2] == Wsp[Czyje[j][h][k]][0] && Wsp[i][1] == Wsp[Czyje[j][h][k]][3])
                                    xd = 0;
                                if(Wsp[i][0] == Wsp[Czyje[j][h][k]][2] && Wsp[i][3] == Wsp[Czyje[j][h][k]][1])
                                    xd = 0;
                                if(Wsp[i][2] == Wsp[Czyje[j][h][k]][0] && Wsp[i][3] == Wsp[Czyje[j][h][k]][1])
                                    xd = 0;
                                if(xd)
                                    List[Czyje[j][h][k]].EB(i), List[i].EB(Czyje[j][h][k]);
                            }
                            else
                                List[Czyje[j][h][k]].EB(i), List[i].EB(Czyje[j][h][k]);
                        }
                    }
            D << "No i fajnie";
        }

        D << "Tak, przeszłam główną pętlę";
        REP(i, d)
        {
            int x, y;
            cin >> x >> y;
            Vis[Czyje[x][y][0]] = 1;
        }
  
        D << "Jeszcze żyję";
        VI x, y;
        x.EB(Czyje[xp][yp][0]);
        Vis[Czyje[xp][yp][0]] = 1;
 
        D << "Jest nadspodziewanie dobrze";
        int dep = 1;
        VI Depth(1e6, 0);
        Depth[Czyje[xp][yp][0]] = 1;
 
        /// BFS
        while(SZ(x))
        {
            REP(i, SZ(x))
                REP(j, SZ(List[x[i]]))
                    if(!Vis[List[x[i]][j]])
                    {
                        Depth[List[x[i]][j]] = dep + 1;
                        Vis[List[x[i]][j]] = 1;
                        y.EB(List[x[i]][j]);
                    }

            swap(x, y);
            y.clear();
            dep++;
        }
        D << "To już prawie finisz";
        return cout << Depth[Czyje[xs][ys][0]], 0;
    }

    REP(i, n)
    {
        cin >> Wsp[i][0] >> Wsp[i][1] >> Wsp[i][2] >> Wsp[i][3];
        if(Wsp[i][0] > Wsp[i][2]) 
            swap(Wsp[i][0], Wsp[i][2]);
        if(Wsp[i][1] > Wsp[i][3]) 
            swap(Wsp[i][1], Wsp[i][3]);
    }

    REP(i, n)
        FOR(j, i + 1, n - 1)
            if(Wsp[j][0] <= Wsp[i][2]  &&  Wsp[j][2] >= Wsp[i][0]  &&  Wsp[j][1] <= Wsp[i][3]  &&  Wsp[j][3] >= Wsp[i][1])
            {
                bool xd = 1;
                if(Wsp[i][0] == Wsp[j][2] && Wsp[i][1] == Wsp[j][3])
                    xd = 0;
                if(Wsp[i][2] == Wsp[j][0] && Wsp[i][1] == Wsp[j][3])
                    xd = 0;
                if(Wsp[i][0] == Wsp[j][2] && Wsp[i][3] == Wsp[j][1])
                    xd = 0;
                if(Wsp[i][2] == Wsp[j][0] && Wsp[i][3] == Wsp[j][1])
                    xd = 0;
                if(xd)
                    List[i].EB(j), List[j].EB(i);
            }

    REP(i, d)
    {
        int x, y;
        cin >> x >> y;
        REP(j, n)
            if(Wsp[j][0] < x  &&  x < Wsp[j][2]  &&  Wsp[j][1] < y  &&  y < Wsp[j][3]) 
                Vis[j] = 1;
    }

    int podr, skarb;

    REP(j, n)
    {
        if(Wsp[j][0] < xs  &&  xs < Wsp[j][2]  &&  Wsp[j][1] < ys  &&  ys < Wsp[j][3]) 
            skarb = j;
        if(Wsp[j][0] < xp  &&  xp < Wsp[j][2]  &&  Wsp[j][1] < yp  &&  yp < Wsp[j][3]) 
            podr = j;
    }

    VI x, y;
    x.EB(podr);
    Vis[podr] = 1;

    int dep = 1;
    VI Depth(1e6, 0);
    Depth[podr] = 1;

    /// BFS
    while(SZ(x))
    {
        REP(i, SZ(x))
            REP(j, SZ(List[x[i]]))
                if(!Vis[List[x[i]][j]])
                {
                    Depth[List[x[i]][j]] = dep + 1;
                    Vis[List[x[i]][j]] = 1;
                    y.EB(List[x[i]][j]);
                }

        swap(x, y);
        y.clear();
        dep++;
    }
 
    return cout << Depth[skarb], 0;
}