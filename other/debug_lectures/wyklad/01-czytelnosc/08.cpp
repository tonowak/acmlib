#include <bits/stdc++.h>

using namespace std;

#ifdef _WIN32
inline int getchar_unlocked() {
    return getchar();
}

inline void putchar_unlocked(int a) {
    putchar(a);
}
#endif // getchar_unlocked

typedef long long ll;
typedef pair<int, int> ii;

const ll MOD = 1e9 + 7;

#define EMPTY   0
#define WALL    1
#define GOOD    2

#define X first
#define Y second

int N, k;
char M[3007][3007];
int singular[4][3007][3007];
ll all_singular[5];

ll pot(ll a, ll k) {
    if(k == 0) return 1LL;

    if(k % 2)
        return (a * pot(a, k - 1)) % MOD;

    ll pom = pot(a, k / 2);
    return (pom * pom) % MOD;
}

inline ll inv(ll x) {
    return pot(x, MOD - 2);
}

#define ok_point(x, y) (((x) >= 1 && (y) >= 1))

template<int k>
struct pattern {
    int n, m;
    int T[k][k];
    vector<ii> bad;

    pattern() {
        n = m = 0;
    };

    pattern(int mask) {
        int i = 1;
        n = m = 0;
        bad.clear();
        for(int x = 0 ; x < k ; x++) {
            for(int y = 0 ; y < k ; y++) {
                T[x][y] = mask & i;
                i <<= 1;
                if(T[x][y]) {
                    n = max(n, x + 1);
                    m = max(m, y + 1);
                }
            }
        }
    }

    int* operator[](int a) {
        return T[a];
    }

    void build_bad() {
        for(int x = 0 ; x < k ; x++) {
            for(int y = 0 ; y < k ; y++) {
                if(T[x][y]) {
                    bad.push_back({x, y});
                    bad.push_back({x - 1, y});
                    bad.push_back({x + 1, y});
                    bad.push_back({x, y - 1});
                    bad.push_back({x, y + 1});
                }
            }
        }

        sort(bad.begin(), bad.end());
        auto it = unique(bad.begin(), bad.end());
        bad.resize(distance(bad.begin(), it));
    }

    bool ok() {
        int cnt = 0;
        ii start;
        for(int x = 0 ; x < k ; x++)
            for(int y = 0 ; y < k ; y++)
                if(T[x][y]) cnt++, start = {x, y};
        if(cnt != k)
            return false;

        bool ok1 = false, ok2 = false;
        for(int i = 0 ; i <  k ; i++) {
            if(T[0][i]) ok1 = true;
            if(T[i][0]) ok2 = true;
        }

        if(!ok1 || !ok2)
            return false;

        bool vis[k][k];
        memset(vis, 0, sizeof vis);
        queue<ii> Q;
        vis[start.X][start.Y] = true;
        Q.push(start);
        while(!Q.empty()) {
            ii p = Q.front();
            Q.pop();

            if(p.X - 1 >= 0 && !vis[p.X - 1][p.Y] && T[p.X - 1][p.Y])
                Q.push({p.X - 1, p.Y}), vis[p.X - 1][p.Y] = true;
            if(p.X + 1 < k && !vis[p.X + 1][p.Y] && T[p.X + 1][p.Y])
                Q.push({p.X + 1, p.Y}), vis[p.X + 1][p.Y] = true;
            if(p.Y - 1 >= 0 && !vis[p.X][p.Y - 1] && T[p.X][p.Y - 1])
                Q.push({p.X, p.Y - 1}), vis[p.X][p.Y - 1] = true;
            if(p.Y + 1 < k && !vis[p.X][p.Y + 1] && T[p.X][p.Y + 1])
                Q.push({p.X, p.Y + 1}), vis[p.X][p.Y + 1] = true;
        }

        for(int x = 0 ; x < k ; x++)
            for(int y = 0 ; y < k ; y++)
                if(T[x][y] && !vis[x][y])
                    return false;

        return true;
    }

    void print() {
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < m ; j++)
                printf("%c", (T[i][j]) ? '#' : ' ');
            printf("\n");
        }
    }

    bool check_place(int x, int y) {
        int cnt_good = 0;
        if(x + n - 1 > N || y + m - 1 > N)
            return false;
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < m ; j++) {
                if(T[i][j]) {
                    if(M[x + i][y + j] == WALL)
                        return false;
                    if(M[x + i][y + j] == GOOD)
                        cnt_good++;
                }
            }
        }
        return cnt_good;
    }

    bool check_place_unsafe(int x, int y) {
        int cnt_good = 0;
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < m ; j++) {
                if(T[i][j]) {
                    if(M[x + i][y + j] == WALL)
                        return false;
                    if(M[x + i][y + j] == GOOD)
                        cnt_good++;
                }
            }
        }
        return cnt_good;
    }

   /* int count() {
        int res = 0;
        int tmpn = N - n + 1;
        int tmpm = N - m + 1;
        for(int x = 1 ; x <= tmpn ; x++)
            for(int y = 1 ; y <= tmpm ; y++)
                if(check_place_unsafe(x, y))
                    res++;
        return res;
    }*/

    /*int count_withp() {
        ll res = 0;
        int tmpn = N - n + 1;
        int tmpm = N - m + 1;
        for(int x = 1 ; x <= tmpn ; x++) {
            for(int y = 1 ; y <= tmpm ; y++) {
                if(check_place_unsafe(x, y)) {
                    res += all_singular[1];
                    for(ii p : bad)
                        if(ok_point(x + p.X, y + p.Y))
                            res -= singular[0][x + p.X][y + p.Y];
                }
            }
        }
        return res % MOD;
    }*/
};

vector<pattern<2> > P2;
vector<pattern<3> > P3;
vector<pattern<4> > P4;

int ok2[2][3020][3020];

#define row_sum(i, x, y1, y2) (ok2[(i)][(x)][(y2)] - ok2[(i)][(x)][max(1, (y1)) - 1])

ll count_2_2() {
    ll all22 = 0;
    for(int x = 1 ; x <= N ; x++) {
        for(int y = 1 ; y <= N ; y++) {
            ok2[0][x][y] = ok2[0][x][y - 1] + ((x + 1 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD)) ? 1 : 0);
            ok2[1][x][y] = ok2[1][x][y - 1] + ((x + 2 - 1 <= N && y + 1 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD)) ? 1 : 0);
        }
        all22 += ok2[0][x][N];
        all22 += ok2[1][x][N];
        for(int y = N + 1 ; y <= N + 4 ; y++) {
            ok2[0][x][y] = ok2[0][x][y - 1];
            ok2[1][x][y] = ok2[1][x][y - 1];
        }
    }
    all22 %= MOD;

    ll res = (all22 * all22) % MOD, res2 = 0;
    for(int x = 1 ; x <= N ; x++) {
        for(int y = 1 ; y <= N ; y++) {
            if(ok2[0][x][y] - ok2[0][x][y - 1]) {
                res -= row_sum(0, x - 1, y - 1, y + 1);
                res -= row_sum(0, x, y - 2, y + 2);
                res -= row_sum(0, x + 1, y - 1, y + 1);

                if(x - 2 >= 1) res -= row_sum(1, x - 2, y, y + 1);
                res -= row_sum(1, x - 1, y - 1, y + 2);
                res -= row_sum(1, x, y - 1, y + 2);
                res -= row_sum(1, x + 1, y, y + 1);

                ll tmp = all_singular[2];
                //if(ok_point(x - 1, y))
                    tmp -= singular[1][x - 1][y];
                //if(ok_point(x - 1, y + 1))
                    tmp -= singular[1][x - 1][y + 1];
                //if(ok_point(x, y - 1))
                    tmp -= singular[1][x][y - 1];
                //if(ok_point(x, y))
                    tmp -= singular[1][x][y];
                //if(ok_point(x, y + 1))
                    tmp -= singular[1][x][y + 1];
                if(y + 2 <= N)
                    tmp -= singular[1][x][y + 2];
                //if(ok_point(x + 1, y))
                    tmp -= singular[1][x + 1][y];
                //if(ok_point(x + 1, y + 1))
                    tmp -= singular[1][x + 1][y + 1];

               /* for(int d = 0 ; d < two_bad_rect[0].size() ; d++) {
                    ii p1 = {x + two_bad_rect[0][d][0].X, y + two_bad_rect[0][d][0].Y};
                    ii p2 = {x + two_bad_rect[0][d][1].X, y + two_bad_rect[0][d][1].Y};
                    if(ok_point(p1.X, p1.Y) && ok_point(p2.X, p2.Y) && M[p1.X][p1.Y] == GOOD && M[p2.X][p2.Y] == GOOD)
                        tmp++;
                }*/

                if(M[x - 1][y] == GOOD) {
                    if(M[x][y - 1] == GOOD)
                        tmp++;
                    if(M[x][y + 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD)
                        tmp++;
                }
                if(M[x - 1][y + 1] == GOOD) {
                    if(M[x][y - 1] == GOOD)
                        tmp++;
                    if(M[x][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD)
                        tmp++;
                }
                if(M[x][y - 1] == GOOD) {
                    if(M[x][y + 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD)
                        tmp++;
                }
                if(M[x][y] == GOOD && M[x + 1][y + 1] == GOOD)
                    tmp++;
                if(M[x][y + 1] == GOOD && M[x + 1][y] == GOOD)
                    tmp++;
                if(y + 2 <= N) {
                    if(M[x][y] == GOOD && M[x][y + 2] == GOOD)
                        tmp++;
                    if(M[x][y + 2] == GOOD && M[x + 1][y] == GOOD)
                        tmp++;
                    if(M[x][y + 2] == GOOD && M[x + 1][y + 1] == GOOD)
                        tmp++;
                    if(M[x - 1][y + 1] == GOOD && M[x][y + 2] == GOOD)
                        tmp++;
                    if(M[x][y - 1] == GOOD && M[x][y + 2] == GOOD)
                        tmp++;
                    if(M[x - 1][y] == GOOD && M[x][y + 2] == GOOD)
                        tmp++;
                }

                tmp %= MOD;
                res2 += tmp;
            }

            if(ok2[1][x][y] - ok2[1][x][y - 1]) {
                res -= row_sum(0, x - 1, y - 1, y);
                res -= row_sum(0, x, y - 2, y + 1);
                res -= row_sum(0, x + 1, y - 2, y + 1);
                res -= row_sum(0, x + 2, y - 1, y);

                if(x - 2 >= 1) res -= row_sum(1, x - 2, y, y);
                res -= row_sum(1, x - 1, y - 1, y + 1);
                res -= row_sum(1, x,  y - 1, y + 1);
                res -= row_sum(1, x + 1, y - 1, y + 1);
                res -= row_sum(1, x + 2, y, y);

                ll tmp = all_singular[2];
                //if(ok_point(x - 1, y))
                    tmp -= singular[1][x - 1][y];
                //if(ok_point(x, y - 1))
                    tmp -= singular[1][x][y - 1];
               // if(ok_point(x, y))
                    tmp -= singular[1][x][y];
               // if(ok_point(x, y + 1))
                    tmp -= singular[1][x][y + 1];
                //if(ok_point(x + 1, y - 1))
                    tmp -= singular[1][x + 1][y - 1];
               // if(ok_point(x + 1, y))
                    tmp -= singular[1][x + 1][y];
               // if(ok_point(x + 1, y + 1))
                    tmp -= singular[1][x + 1][y + 1];
                if(x + 2 <= N)
                    tmp -= singular[1][x + 2][y];

                /*for(int d = 0 ; d < two_bad_rect[1].size() ; d++) {
                    ii p1 = {x + two_bad_rect[1][d][0].X, y + two_bad_rect[1][d][0].Y};
                    ii p2 = {x + two_bad_rect[1][d][1].X, y + two_bad_rect[1][d][1].Y};
                    if(ok_point(p1.X, p1.Y) && ok_point(p2.X, p2.Y) && M[p1.X][p1.Y] == GOOD && M[p2.X][p2.Y] == GOOD)
                        tmp++;
                }*/

                if(M[x - 1][y] == GOOD) {
                    if(M[x][y - 1] == GOOD)
                        tmp++;
                    if(M[x][y + 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y - 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD)
                        tmp++;
                }
                if(M[x][y - 1] == GOOD) {
                    if(M[x][y + 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD)
                        tmp++;
                }
                if(M[x][y] == GOOD) {
                    if(M[x + 1][y - 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD)
                        tmp++;
                }
                if(M[x][y + 1] == GOOD) {
                    if(M[x + 1][y - 1] == GOOD)
                        tmp++;
                    if(M[x + 1][y] == GOOD)
                        tmp++;
                }
                if(M[x + 1][y - 1] == GOOD && M[x + 1][y + 1] == GOOD)
                    tmp++;
                if(x + 2 <= N) {
                    if(M[x][y] == GOOD && M[x + 2][y] == GOOD)
                        tmp++;
                    if(M[x][y + 1] == GOOD && M[x + 2][y] == GOOD)
                        tmp++;
                    if(M[x][y - 1] == GOOD && M[x + 2][y] == GOOD)
                        tmp++;
                    if(M[x - 1][y] == GOOD && M[x + 2][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y - 1] == GOOD && M[x + 2][y] == GOOD)
                        tmp++;
                    if(M[x + 1][y + 1] == GOOD && M[x + 2][y] == GOOD)
                        tmp++;
                }

                tmp %= MOD;
                res2 += tmp;
            }
        }
    }

    res = (res % MOD + MOD) % MOD;
    res *= inv(2);
    res = (res % MOD + MOD) % MOD;
    res += res2;
    res = (res % MOD + MOD) % MOD;
    return res;
}

inline int dist(int ax, int ay, int bx, int by) {
    return abs(ax - bx) + abs(ay - by);
}

ll triples_with(int ax, int ay, int bx, int by) {
    ll tmp = all_singular[1];
    tmp -= singular[0][ax][ay];
    tmp -= singular[0][ax + 1][ay];
    tmp -= singular[0][ax - 1][ay];
    tmp -= singular[0][ax][ay + 1];
    tmp -= singular[0][ax][ay - 1];
    if(dist(bx, by, ax, ay) > 1)
        tmp -= singular[0][bx][by];
    if(dist(bx + 1, by, ax, ay) > 1)
        tmp -= singular[0][bx + 1][by];
    if(dist(bx - 1, by, ax, ay) > 1)
        tmp -= singular[0][bx - 1][by];
    if(dist(bx, by + 1, ax, ay) > 1)
        tmp -= singular[0][bx][by + 1];
    if(dist(bx, by - 1, ax, ay) > 1)
        tmp -= singular[0][bx][by - 1];
    return tmp;
}

/*inline int check_point(int x, int y) {
    if(M[x][y] == GOOD)
        return 1;
    return 0;
}*/

string pompom(int x) {
    if(x == 0)
        return "";
    if(x == -1)
        return " - 1";
    if(x == 1)
        return " + 1";
    if(x == 2)
        return " + 2";
    if(x == -2)
        return " - 2";
    if(x == 3)
        return " + 3";
    if(x == 4)
        return " + 4";
}

int main() {
    scanf("%d %d", &N, &k);
    //N = 3000;
    //k = 4;
    //srand(time(NULL));

    char tmp;
    for(int i = 1 ; i <= N ; i++) {
        for(int j = 1 ; j <= N ; j++) {
            do {
                tmp = getchar_unlocked();
            } while(tmp != '#' && tmp != '.');
            M[i][j] = (tmp == '#') ? WALL : EMPTY;
            //M[i][j] = (rand() % 5) ? EMPTY : WALL;
        }
    }

    for(int i = 1 ; i <= N ; i++)
        for(int j = 1 ; j <= N ; j++)
            if(M[i][j] == EMPTY && (M[i - 1][j] == WALL || M[i + 1][j] == WALL
                || M[i][j - 1] == WALL || M[i][j + 1] == WALL))
                    M[i][j] = GOOD;

    if(k == 1) {
        int cnt = 0;
        for(int i = 1 ; i <= N ; i++)
            for(int j = 1 ; j <= N ; j++)
                if(M[i][j] == GOOD)
                    cnt++;
        printf("%d\n", cnt);
        return 0;
    }

    P2.emplace_back(3);
    P2.back().build_bad();
    P2.emplace_back(5);
    P2.back().build_bad();

    if(k >= 3) {
        /*pattern<3> p;
        for(int mask = 0 ; mask < (1 << 9) ; mask++) {
            p = pattern<3>(mask);
            if(p.ok()) {
                cout << mask << endl;
                p.build_bad();
                P3.push_back(p);
            }
        }*/
        P3.emplace_back(7);
        P3.back().build_bad();
        P3.emplace_back(11);
        P3.back().build_bad();
        P3.emplace_back(19);
        P3.back().build_bad();
        P3.emplace_back(25);
        P3.back().build_bad();
        P3.emplace_back(26);
        P3.back().build_bad();
        P3.emplace_back(73);
        P3.back().build_bad();
    }

    if(k >= 4) {
        /*pattern<4> p;
        for(int mask = 0 ; mask < (1 << 16) ; mask++) {
            p = pattern<4>(mask);
            if(p.ok()) {
                p.build_bad();
                P4.push_back(p);
            }
        }*/
        P4.emplace_back(15);
        P4.emplace_back(23);
        P4.emplace_back(39);
        P4.emplace_back(51);
        P4.emplace_back(54);
        P4.emplace_back(71);
        P4.emplace_back(99);
        P4.emplace_back(113);
        P4.emplace_back(114);
        P4.emplace_back(116);
        P4.emplace_back(275);
        P4.emplace_back(305);
        P4.emplace_back(306);
        P4.emplace_back(547);
        P4.emplace_back(561);
        P4.emplace_back(562);
        P4.emplace_back(785);
        P4.emplace_back(802);
        P4.emplace_back(4369);
    }

    for(int i = 1 ; i <= N ; i++) {
        for(int j = 1 ; j <= N ; j++) {
            singular[0][i][j] = (M[i][j] == GOOD) ? 1 : 0;
            all_singular[1] += singular[0][i][j];
        }
    }

    for(int l = 1 ; l < k ; l++) {
        for(int x = 1 ; x <= N ; x++) {
            for(int y = 1 ; y <= N ; y++) {
                if(M[x][y] != GOOD) {
                    continue;
                }

                ll tmp = all_singular[l];

                tmp -= singular[l - 1][x][y];
                tmp -= singular[l - 1][x - 1][y];
                tmp -= singular[l - 1][x + 1][y];
                tmp -= singular[l - 1][x][y - 1];
                tmp -= singular[l - 1][x][y + 1];

                if(l == 2) {
                    int xx = 0;
                    xx += (M[x - 1][y] & M[x + 1][y]) >> 1;
                    xx += (M[x][y - 1] & M[x][y + 1]) >> 1;
                    xx += (M[x - 1][y] & M[x][y + 1]) >> 1;
                    xx += (M[x][y + 1] & M[x + 1][y]) >> 1;
                    xx += (M[x + 1][y] & M[x][y - 1]) >> 1;
                    xx += (M[x][y - 1] & M[x - 1][y]) >> 1;
                    tmp += ll(xx);
                }

                if(l == 3) {
                    if((M[x - 1][y] & M[x + 1][y]) >> 1)
                        tmp += triples_with(x - 1, y, x + 1, y);
                    if((M[x][y - 1] & M[x][y + 1]) >> 1)
                        tmp += triples_with(x, y - 1, x, y + 1);
                    if((M[x - 1][y] & M[x][y + 1]) >> 1)
                        tmp += triples_with(x - 1, y, x, y + 1);
                    if((M[x][y + 1] & M[x + 1][y]) >> 1)
                        tmp += triples_with(x, y + 1, x + 1, y);
                    if((M[x + 1][y] & M[x][y - 1]) >> 1)
                        tmp += triples_with(x + 1, y, x, y - 1);
                    if((M[x][y - 1] & M[x - 1][y]) >> 1)
                        tmp += triples_with(x, y - 1, x - 1, y);

                    int xx = 0;
                    xx -= (M[x - 1][y] & M[x][y + 1] & M[x + 1][y]) >> 1;
                    xx -= (M[x][y + 1] & M[x + 1][y] & M[x][y - 1]) >> 1;
                    xx -= (M[x + 1][y] & M[x][y - 1] & M[x - 1][y]) >> 1;
                    xx -= (M[x][y - 1] & M[x - 1][y] & M[x][y + 1]) >> 1;
                    tmp += ll(xx);
                }

                tmp %= MOD;
                singular[l][x][y] = tmp;
                all_singular[l + 1] += tmp;
            }
        }

        all_singular[l + 1] %= MOD;
        all_singular[l + 1] *= inv(l + 1);
        all_singular[l + 1] = (all_singular[l + 1] % MOD + MOD) % MOD;
    }

    if(k == 2) {
        ll res = 0;
        res += all_singular[2];
        for(int x = 1 ; x <= N ; x++) {
            for(int y = 1 ; y <= N ; y++) {
                if(x + 1 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD)) res++;
                if(x + 2 - 1 <= N && y + 1 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD)) res++;
            }
        }

        res = (res % MOD + MOD) % MOD;
        printf("%lld\n", res);
        return 0;
    }

    if(k == 3) {
        ll res = 0;
        res += all_singular[3];

        for(int x = 1 ; x <= N ; x++) {
            for(int y = 1 ; y <= N ; y++) {
                if(x + 1 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x][y + 2] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x][y + 2] == GOOD)) res++;
                if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y] == GOOD)) res++;
                if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y + 1] == GOOD)) res++;
                if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD)) res++;
                if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && (M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD)) res++;
                if(x + 3 - 1 <= N && y + 1 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 2][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 2][y] == GOOD)) res++;
            }
        }

        for(int x = 1 ; x <= N ; x++) {
            for(int y = 1 ; y <= N ; y++) {
                if(x + 1 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD)) {
                    res += all_singular[1];
                    for(ii p : P2[0].bad)
                        if(ok_point(x + p.X, y + p.Y))
                            res -= singular[0][x + p.X][y + p.Y];
                }
                if(x + 2 - 1 <= N && y + 1 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD)) {
                    res += all_singular[1];
                    for(ii p : P2[1].bad)
                        if(ok_point(x + p.X, y + p.Y))
                            res -= singular[0][x + p.X][y + p.Y];
                }
            }
        }

        res = (res % MOD + MOD) % MOD;
        printf("%lld\n", res);
        return 0;
    }

    ll res = 0;
    res += all_singular[4];
    res += count_2_2();

    res %= MOD;
    for(int x = 1 ; x <= N ; x++) {
        for(int y = 1 ; y <= N ; y++) {
            if(x + 1 - 1 <= N && y + 4 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x][y + 2] != WALL && M[x][y + 3] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x][y + 2] == GOOD || M[x][y + 3] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x][y + 2] != WALL && M[x + 1][y] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x][y + 2] == GOOD || M[x + 1][y] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x][y + 2] != WALL && M[x + 1][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x][y + 2] == GOOD || M[x + 1][y + 1] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y + 1] != WALL && M[x][y + 2] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && (M[x][y + 1] == GOOD || M[x][y + 2] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x][y + 2] != WALL && M[x + 1][y + 2] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x][y + 2] == GOOD || M[x + 1][y + 2] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y + 1] != WALL && M[x + 1][y + 2] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 1][y + 2] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 1][y + 2] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 1][y + 2] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 1][y + 2] != WALL && (M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 1][y + 2] == GOOD)) res++;
            if(x + 2 - 1 <= N && y + 3 - 1 <= N && M[x][y + 2] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 1][y + 2] != WALL && (M[x][y + 2] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 1][y + 2] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 2][y] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 2][y] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 2][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 2][y] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 2][y] != WALL && (M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 2][y] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y + 1] != WALL && M[x + 2][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 2][y + 1] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 2][y + 1] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 2][y + 1] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && M[x + 2][y + 1] != WALL && (M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 2][y + 1] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 2][y] != WALL && M[x + 2][y + 1] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 2][y] == GOOD || M[x + 2][y + 1] == GOOD)) res++;
            if(x + 3 - 1 <= N && y + 2 - 1 <= N && M[x][y + 1] != WALL && M[x + 1][y + 1] != WALL && M[x + 2][y] != WALL && M[x + 2][y + 1] != WALL && (M[x][y + 1] == GOOD || M[x + 1][y + 1] == GOOD || M[x + 2][y] == GOOD || M[x + 2][y + 1] == GOOD)) res++;
            if(x + 4 - 1 <= N && y + 1 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 2][y] != WALL && M[x + 3][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 2][y] == GOOD || M[x + 3][y] == GOOD)) res++;
        }
    }

    res %= MOD;
    for(int x = 1 ; x <= N ; x++) {
        for(int y = 1 ; y <= N ; y++) {
            if(x + 1 - 1 <= N && y + 3 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x][y + 2] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x][y + 2] == GOOD)) {
                res += all_singular[1];
                for(ii p : P3[0].bad)
                    if(ok_point(x + p.X, y + p.Y))
                        res -= singular[0][x + p.X][y + p.Y];
            }
            if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y] == GOOD)) {
                res += all_singular[1];
                for(ii p : P3[1].bad)
                    if(ok_point(x + p.X, y + p.Y))
                        res -= singular[0][x + p.X][y + p.Y];
            }
            if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x][y + 1] != WALL && M[x + 1][y + 1] != WALL && (M[x][y] == GOOD || M[x][y + 1] == GOOD || M[x + 1][y + 1] == GOOD)) {
                res += all_singular[1];
                for(ii p : P3[2].bad)
                    if(ok_point(x + p.X, y + p.Y))
                        res -= singular[0][x + p.X][y + p.Y];
            }
            if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD)) {
                res += all_singular[1];
                for(ii p : P3[3].bad)
                    if(ok_point(x + p.X, y + p.Y))
                        res -= singular[0][x + p.X][y + p.Y];
            }
            if(x + 2 - 1 <= N && y + 2 - 1 <= N && M[x][y + 1] != WALL && M[x + 1][y] != WALL && M[x + 1][y + 1] != WALL && (M[x][y + 1] == GOOD || M[x + 1][y] == GOOD || M[x + 1][y + 1] == GOOD)) {
                res += all_singular[1];
                for(ii p : P3[4].bad)
                    if(ok_point(x + p.X, y + p.Y))
                        res -= singular[0][x + p.X][y + p.Y];
            }
            if(x + 3 - 1 <= N && y + 1 - 1 <= N && M[x][y] != WALL && M[x + 1][y] != WALL && M[x + 2][y] != WALL && (M[x][y] == GOOD || M[x + 1][y] == GOOD || M[x + 2][y] == GOOD)) {
                res += all_singular[1];
                for(ii p : P3[5].bad)
                    if(ok_point(x + p.X, y + p.Y))
                        res -= singular[0][x + p.X][y + p.Y];
            }
        }
    }

    res = (res % MOD + MOD) % MOD;
    printf("%lld\n", res);
    return 0;
}