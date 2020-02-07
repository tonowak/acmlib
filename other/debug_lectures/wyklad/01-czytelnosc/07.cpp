#include <bits/stdc++.h>
 
using namespace std;
 
#define FOR(i,a,n) for (decltype(n) i = (a), i ## __ = (n); i <= i ## __; ++i)
#define FORD(i,a,n) for (decltype(n) i = (a), i ## __ = (n); i >= i ## __; --i)
#define REP(i,n) FOR(i, 0, n - 1)
#define REPD(i, n) FORD(i, n - 1, 0)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define EB emplace_back
#define V vector
#define ST first
#define ND second
#define RS resize
 
template<class T, class B> inline void mini(T &&a, B &&b) { if (b < a) a = b; }
template<class T, class B> inline void maxi(T &&a, B &&b) { if (b > a) a = b; }
int ceil2(int x) { return x < 2 ? 1 : 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }
 
constexpr char nl = '\n';
template<class T> struct DumpOff { T a, b; };
template<class T> auto dumpOff(T &x) -> DumpOff<decltype(x.begin())> { return {x.begin(), x.end()}; }
template<class T> auto dumpOff(T &x) -> decltype(cerr << x, x) { return x; }
template<class T> auto dumpOff(T &x) -> decltype(x.first, x) { return x; }
struct Debug {
    ~Debug() { cerr << nl; }
    template<class T> auto operator<<(T x) -> decltype(cerr << x, *this) { cerr << dumpOff(x); return *this; }
    template<class T> auto operator<<(T x) -> decltype(x.begin(), *this) {
        cerr << "{\n";
        for (auto a = x.begin(), b = x.end(); a != b; ++a)
            *this << "  " << distance(x.begin(), a) << ": " << dumpOff(*a) << '\n';
        return *this << "}";
    }
    template<class T, class B> Debug& operator<<(pair<T, B> p) { return *this << "(" << dumpOff(p.first) << ", " << dumpOff(p.second) << ")"; }
    template<class T> Debug& operator<<(DumpOff<T> d) {
        cerr << "{";
        for (auto a = d.a, b = d.b; a != b; ++a)
            *this << dumpOff(*a) << (next(a) == b ? "" : ", ");
        return *this << "}";
    }
};
struct Foo {template<class T>Foo& operator<<(T) {return *this;}};
 
#ifdef DEBUG
# define D Debug()
#else
# define D Foo()
#endif
#define I(x...) #x ": " << x << "   "
 
typedef long long LL;
typedef pair<LL, LL> PII;
typedef V<int> VI;
typedef V<VI> VVI;
typedef V<PII> VPII;
typedef V<VPII> VVPII;
typedef V<bool> VB;
typedef V<VB> VVB;
typedef V<LL> VLL;
typedef V<VLL> VVLL;

int n, k;
array<int, 4> x_help = {{1, 0, -1, 0}}, y_help = {{0, -1, 0, 1}};

inline bool valid(int x, int y) 
{
    return 0 <= x && x < n && 0 <= y && y < n;
}

VVI BFS(VVB &v)
{
    VVI ans(n, VI(n, 5));
    deque<PII> q;

    REP(i, n) REP(j, n) if(v[i][j]) ans[i][j] = 0, q.EB(i, j);
    while(SZ(q)) 
    {
        int x, y;
        x = q.front().ST, y = q.front().ND;
        q.pop_front();

        REP(side, 4) 
        {
            int i = x_help[side], j = y_help[side];
            if(valid(x + i, y + j) && ans[x][y] < ans[x + i][y + j]) 
            {
                ans[x + i][y + j] = ans[x][y] + 1;
                q.EB(x + i, y + j);
            }
        }
    }
    return ans;
}

inline void mod(LL &a)
{
    if(a > 1000000007) a %= 1000000007;
}

inline bool fin()
{
    char c = 0;
    while (c != '.' && c != '#') c = getc_unlocked(stdin);
    if(c == '#') return 1;
    return 0;
}

int main()
{
    scanf("%d %d", &n, &k);
    VVB v(n, VB(n));
    REP(i, n) REP(j, n)
        v[i][j] = fin();

    VVI d = BFS(v);    
    LL a = 0;
    REP(i, n) REP(j, n) if(d[i][j] == 1) ++a;

    if(k == 1)
        cout << a << "\n";
    if(k == 2)
    {
        //1 1
        LL wyn = a * (a - 1) / 2;

        //1 2
        REP(i, n) REP(j, n)
        {
            if(d[i][j] == 1)
            {
                REP(side, 4)
                {
                    int xh = x_help[side], yh = y_help[side];
                    if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2) ++wyn;
                }
            }
        }

        mod(wyn);
        printf("%lld\n", wyn);
    }
    if(k == 3)
    {

        // 1 1 1
        LL x1 = a;
        LL x2 = a - 1;
        LL x3 = a - 2;

        if(x1 % 3 == 0) x1 /= 3;
        else if(x2 % 3 == 0) x2 /= 3;
        else if(x3 % 3 == 0) x3 /= 3;

        if(x1 % 2 == 0) x1 /= 2;
        else if(x2 % 2 == 0) x2 /= 2;
        else if(x3 % 2 == 0) x3 /= 2;

        x1 *= x2;
        mod(x1);

        LL wyn = x1 * x3;
        mod(wyn);


        // 1 1 2
        VVLL jed(n, VLL(n));
        REP(i, n) REP(j, n)
        {
            if(d[i][j] == 2)
            {
                LL xd = 0;
                REP(side, 4)
                {
                    int xh = x_help[side], yh = y_help[side];
                    if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 1) xd++;
                }
                jed[i][j] = xd;
                wyn += xd * (a - xd) + xd * (xd - 1) / 2;
                mod(wyn);
            }
        }


        // 1 2 2
        REP(i, n) REP(j, n)
        {
            if(d[i][j] == 1)
            {
                LL xd = 0;
                REP(side, 4)
                {
                    int xh = x_help[side], yh = y_help[side];
                    if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2) xd++;
                }

                REP(side, 4)
                {
                    int xh = x_help[side], yh = y_help[side];
                    if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2)
                    {
                        int shitcounter = 0;
                        REP(side2, 4)
                        {
                            int deeperx = i + xh + x_help[side2], deepery = j + yh + y_help[side2];
                            if(valid(deeperx, deepery) && d[deeperx][deepery] == 2)
                                shitcounter++;
                        }
                        wyn += xd - 1 + shitcounter;
                        mod(wyn);
                        xd--;
                    }
                }
            }
        }


        // 1 2 3
        REP(i, n) REP(j, n)
        {
            if(d[i][j] == 3)
            {
                LL xd = 0;
                REP(side, 4)
                {
                    int xh = x_help[side], yh = y_help[side];
                    if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2) xd += jed[i + xh][j + yh];
                }
                wyn += xd;
                mod(wyn);
            }
        }

        printf("%lld\n", wyn);
    } 

    if(k == 4)
    {   
        VPII a1;
        VPII a2;
        VPII a3;
        VPII a4;

        REP(i, n) REP(j, n)
        {
            if(d[i][j] == 1) a1.EB(i, j);
            if(d[i][j] == 2) a2.EB(i, j);
            if(d[i][j] == 3) a3.EB(i, j);
            if(d[i][j] == 4) a4.EB(i, j);
        }

        LL x1 = a;
        LL x2 = a - 1;
        LL x3 = a - 2;
        LL x4 = a - 3;

        if(x1 % 4 == 0) x1 /= 4;
        else if(x2 % 4 == 0) x2 /= 4;
        else if(x3 % 4 == 0) x3 /= 4;
        else if(x4 % 4 == 0) x4 /= 4;

        if(x1 % 3 == 0) x1 /= 3;
        else if(x2 % 3 == 0) x2 /= 3;
        else if(x3 % 3 == 0) x3 /= 3;
        else if(x4 % 3 == 0) x4 /= 3;

        if(x1 % 2 == 0) x1 /= 2;
        else if(x2 % 2 == 0) x2 /= 2;
        else if(x3 % 2 == 0) x3 /= 2;
        else if(x4 % 2 == 0) x4 /= 2;

        x1 *= x2;
        mod(x1);
        x1 *= x3;
        mod(x1);
        x1 *= x4;

        LL wyn = x1;
        mod(wyn);
                
        REP(x, SZ(a2))
        {
            int i = a2[x].ST, j = a2[x].ND;
            LL xd = 0;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 1) xd++;
            }
            LL part1 = xd * (xd - 1) / 2;
            part1 *= (a - xd);
            mod(part1);
            LL part2 = xd * (a - xd) * (a - xd - 1) / 2;
            mod(part2);
            wyn += part1 + part2 + xd * (xd - 1) * (xd - 2) / 6;
            mod(wyn);
        }
        
                
        //1 2 2 i 1

        LL sztos = 0;
        REP(x, SZ(a1))
        {
            int i = a1[x].ST, j = a1[x].ND;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2)
                {
                    REP(side2, 4)
                    {
                        if(side == side2) continue;
                        int deeperx = i + x_help[side2];
                        int deepery = j + y_help[side2];
                        if(valid(deeperx, deepery) && d[deeperx][deepery] == 2)
                        {
                            LL xd = 0;
                            REP(side3, 4)
                            {
                                int xxh = x_help[side3], yyh = y_help[side3];
                                if(valid(deeperx + xxh, deepery + yyh) && d[deeperx + xxh][deepery + yyh] == 1)
                                    xd++;
                                if(valid(i + xh + xxh, j + yh + yyh) && d[i + xh + xxh][j + yh + yyh] == 1)
                                    if(abs(deeperx - (i + xh + xxh)) + abs(deepery - (j + yh + yyh)) != 1)
                                        xd++;
                            }
                            sztos += a - xd;
                        }
                    }

                    REP(side2, 4)
                    {                            
                        int deeperx = i + xh + x_help[side2];
                        int deepery = j + yh + y_help[side2];
                        if(valid(deeperx, deepery) && d[deeperx][deepery] == 2)
                        {                                
                            LL xd = 1;
                            REP(side3, 4)
                            {
                                int xxh = x_help[side3], yyh = y_help[side3];
                                if(valid(deeperx + xxh, deepery + yyh) && d[deeperx + xxh][deepery + yyh] == 1)
                                    xd++;
                                if(!(xh + xxh == 0 && yh + yyh == 0) && valid(i + xh + xxh, j + yh + yyh) && d[i + xh + xxh][j + yh + yyh] == 1)
                                    sztos--;
                            }
                            wyn += (a - xd);
                            mod(wyn);                               
                        }
                    }
                }
            }
        }
        wyn += sztos / 2;
        mod(wyn);

        //1 2 i 1 2
        LL lol = 0;
        REP(x, SZ(a1))
        {
            int i = a1[x].ST, j = a1[x].ND;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2) lol++;
            }
        }
        mod(lol);
        LL beka = 0;
        REP(x, SZ(a1))
        {
            int i = a1[x].ST, j = a1[x].ND;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2)
                {
                    LL dx = -1;
                    REP(side2, 4)
                    {
                        int deeperx = i + xh + x_help[side2];
                        int deepery = j + yh + y_help[side2];
                        if(valid(deeperx, deepery) && d[deeperx][deepery] == 1) dx++;

                        deeperx = i + x_help[side2];
                        deepery = j + y_help[side2];
                        if(valid(deeperx, deepery) && d[deeperx][deepery] == 2) dx++;
                    }
                    beka += lol - dx;
                }
            }

            if(valid(i + 1, j) && d[i + 1][j] == 2 && valid(i, j + 1) && d[i][j + 1] == 2 && valid(i + 1, j + 1) && d[i + 1][j + 1] == 1)
                wyn--;
        }

        mod(wyn);

        REP(x, SZ(a2))
        {
            int i = a2[x].ST, j = a2[x].ND;
            if(valid(i + 1, j) && d[i + 1][j] == 1 && valid(i, j + 1) && d[i][j + 1] == 1 && valid(i + 1, j + 1) && d[i + 1][j + 1] == 2)
                wyn--;
        }

        wyn += beka / 2;
        mod(wyn);

        REP(x, SZ(a2))
        {
            int i = a2[x].ST, j = a2[x].ND;
            LL xd = 0;
            LL dx = 0;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 1) xd++;
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 3) dx++;
            }
            wyn += (xd * (a - xd) + xd * (xd - 1) / 2) * dx;
            mod(wyn);
        }
             
        REP(x, SZ(a1))
        {
            int i = a1[x].ST, j = a1[x].ND;
            int lol = 0;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 2)
                {
                    lol++;
                    int leftx = xh, lefty = yh;
                    int upx = x_help[(side + 1) % 4], upy = y_help[(side + 1) % 4];
                    int rightx = xh * -1, righty = yh * -1;
                    int downx = upx * -1, downy = upy * -1;
                    int shit = 0;                        

                    if(valid(i + 2 * leftx, j + 2 * lefty) && d[i + 2 * leftx][j + 2 * lefty] == 2)
                    {
                        if(valid(i + 3 * leftx, j + 3 * lefty) && d[i + 3 * leftx][j + 3 * lefty] == 2)
                            shit++;
                        if(valid(i + 2 * leftx + upx, j + 2 * lefty + upy) && d[i + 2 * leftx + upx][j + 2 * lefty + upy] == 2)
                            shit++;
                        if(valid(i + 2 * leftx + downx, j + 2 * lefty + downy) && d[i + 2 * leftx + downx][j + 2 * lefty + downy] == 2)
                            shit++;
                        if(valid(i + leftx + upx, j + lefty + upy) && d[i + leftx + upx][j + lefty + upy] == 2)
                            shit++;
                        if(valid(i + leftx + downx, j + lefty + downy) && d[i + leftx + downx][j + lefty + downy] == 2)
                            shit++;
                        if(valid(i + upx, j + upy) && d[i + upx][j + upy] == 2)
                            shit++;
                        if(valid(i + downx, j + downy) && d[i + downx][j + downy] == 2)
                            shit++;
                        if(valid(i + rightx, j + righty) && d[i + rightx][j + righty] == 2)
                            shit++; 
                    }
                                                                    
                    if(valid(i + upx + leftx, j + upy + lefty) && d[i + upx + leftx][j + upy + lefty] == 2)
                    {

                        if(valid(i + 2 * upx + leftx, j + 2 * upy + lefty) && d[i + 2 * upx + leftx][j + 2 * upy + lefty] == 2)
                            shit++;

                        if(valid(i + upx + 2 * leftx, j + upy + 2 * lefty) && d[i + upx + 2 * leftx][j + upy + 2 * lefty] == 2)                         
                            shit++;

                        ///
                        if(valid(i + upx, j + upy) && d[i + upx][j + upy] == 2)
                            shit++;

                        if(valid(i + downx + leftx, j + downy + lefty) && d[i + downx + leftx][j + downy + lefty] == 2)
                            shit++;
                        ///

                        if(valid(i + rightx, j + righty) && d[i + rightx][j + righty] == 2)
                            shit++;

                        if(valid(i + downx, j + downy) && d[i + downx][j + downy] == 2)
                            shit++;
                    }
                    
                    
                    if(valid(i + downx + leftx, j + downy + lefty) && d[i + downx + leftx][j + downy + lefty] == 2)
                    {
                        if(valid(i + 2 * downx + leftx, j + 2 * downy + lefty) && d[i + 2 * downx + leftx][j + 2 * downy + lefty] == 2)
                            shit++;

                        if(valid(i + downx + 2 * leftx, j + downy + 2 * lefty) && d[i + downx + 2 * leftx][j + downy + 2 * lefty] == 2)                         
                            shit++;

                        if(valid(i + rightx, j + righty) && d[i + rightx][j + righty] == 2)
                            shit++;

                        if(valid(i + upx, j + upy) && d[i + upx][j + upy] == 2)
                            shit++;
                    }
                    

                    wyn += shit;
                    mod(wyn);
                }
            }
            if(lol == 3) wyn++;
            if(lol == 4) wyn += 4;
        }  
        mod(wyn);
        REP(x, SZ(a3))
        {
            int i = a3[x].ST, j = a3[x].ND;
            REP(side, 4) 
            {
                int x1 = i + x_help[side], y1 = j + y_help[side];
                if(valid(x1, y1) && d[x1][y1] == 2)
                {
                    FOR(side2, side + 1, 3)
                    {
                        int x2 = i + x_help[side2], y2 = j + y_help[side2];
                        if(valid(x2, y2) && d[x2][y2] == 2)
                        {
                            int shit = 0;
                            REP(side3, 4)
                            {
                                int xxh = x_help[side3], yyh = y_help[side3];
                                if(valid(x1 + xxh, y1 + yyh) && d[x1 + xxh][y1 + yyh] == 1)
                                    shit++;
                                if(valid(x2 + xxh, y2 + yyh) && d[x2 + xxh][y2 + yyh] == 1)
                                    if(abs(x1 - (x2 + xxh)) + abs(y1 - (y2 + yyh)) != 1)
                                        shit++;
                            }
                            wyn += shit;
                            mod(wyn);
                        } 
                    }

                    REP(side2, 4)
                    {
                        int x2 = x1 + x_help[side2], y2 = y1 + y_help[side2];
                        if(valid(x2, y2) && d[x2][y2] == 2)
                        {
                            int shit = 0;
                            REP(side3, 4)
                            {
                                int xxh = x_help[side3], yyh = y_help[side3];
                                if(valid(x1 + xxh, y1 + yyh) && d[x1 + xxh][y1 + yyh] == 1)
                                    shit++;
                                if(valid(x2 + xxh, y2 + yyh) && d[x2 + xxh][y2 + yyh] == 1)
                                    shit++;
                            }
                            wyn += shit;
                            mod(wyn);
                        }
                    }
                }
            }
        }

        REP(x, SZ(a1))
        {
            int i = a1[x].ST, j = a1[x].ND;
            REP(side, 4) FOR(side2, side + 1, 3)
            {
                int x1 = i + x_help[side], y1 = j + y_help[side];
                int x2 = i + x_help[side2], y2 = j + y_help[side2];
                if(valid(x1, y1) && valid(x2, y2) && d[x1][y1] == 2 && d[x2][y2] == 2)
                {
                    LL shit = 0;
                    REP(side3, 4)
                    {
                        int xxh = x_help[side3], yyh = y_help[side3];
                        if(valid(x1 + xxh, y1 + yyh) && d[x1 + xxh][y1 + yyh] == 3)
                            if(abs(x1 + xxh - x2) + abs(y1 + yyh - y2) != 1)
                                shit++;
                        if(valid(x2 + xxh, y2 + yyh) && d[x2 + xxh][y2 + yyh] == 3)
                            if(abs(x1 - (x2 + xxh)) + abs(y1 - (y2 + yyh)) != 1)
                                shit++;
                    }
                    wyn += shit;
                    mod(wyn);
                } 
            }
        }

        
                
        REP(x, SZ(a2))
        {
            int i = a2[x].ST, j = a2[x].ND;
            LL lolbekaxd = 0;
            LL xd = 0, dx = 0;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 3) xd++;
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 1) dx++;
            }

            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 3)
                {
                    LL shitcounter = 0;
                    REP(side2, 4)
                    {
                        int deeperx = i + xh + x_help[side2], deepery = j + yh + y_help[side2];
                        if(valid(deeperx, deepery) && d[deeperx][deepery] == 3)
                            shitcounter++;
                    }
                    lolbekaxd += xd - 1 + shitcounter;
                    xd--;
                }
            }
            mod(dx), mod(lolbekaxd);
            wyn += dx * lolbekaxd;
            mod(wyn);
        }
        
                
        REP(x, SZ(a4))
        {
            int i = a4[x].ST, j = a4[x].ND;
            LL xd = 0;
            REP(side, 4)
            {
                int xh = x_help[side], yh = y_help[side];
                if(valid(i + xh, j + yh) && d[i + xh][j + yh] == 3)
                {
                    REP(side2, 4)
                    {
                        int deeperx = i + xh + x_help[side2];
                        int deepery = j + yh + y_help[side2];
                        if(valid(deeperx, deepery) && d[deeperx][deepery] == 2)
                        {
                            REP(side3, 4)
                            {
                                int deeperdeeperx = deeperx + x_help[side3];
                                int deeperdeepery = deepery + y_help[side3];
                                if(valid(deeperdeeperx, deeperdeepery) && d[deeperdeeperx][deeperdeepery] == 1) xd++;
                            }
                        }
                    }
                }
            }
            wyn += xd;
            mod(wyn);
        }

       printf("%lld\n", wyn);
    }
}