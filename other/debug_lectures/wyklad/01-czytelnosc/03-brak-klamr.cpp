int mex(VI &v) {
    VB is(SZ(v) + 1);
    for(int i : v)
        if(i <= SZ(v))
            is[i] = 1;
    REP(i, SZ(is))
        if(!is[i])
            return i;
    return -1;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int h, w;
    cin >> h >> w;
    VVI good(w, VI(h, 1));
    REP(y, h)
        REP(x, w) {
            char c;
            cin >> c;
            good[x][y] = c == '.';
        }
    D << I(h) << I(w) << I(good);
 
    V< V<VVI> > nimber(w, V<VVI>(w, VVI(h, VI(h))));
    FOR(dx, 1, w)
        REP(l, w - dx + 1)
            FOR(dy, 1, h)
                REP(d, h - dy + 1) {
                    int r = l + dx - 1, u = d + dy - 1;
                    VI vals;
                    FOR(x, l, r)
                        FOR(y, d, u)
                            if(good[x][y]) {
                                int ksor = 0;
                                if(x != l && y != u)
                                    ksor ^= nimber[l][x - 1][y + 1][u];
                                if(x != l && y != d)
                                    ksor ^= nimber[l][x - 1][d][y - 1];
                                if(x != r && y != u)
                                    ksor ^= nimber[x + 1][r][y + 1][u];
                                if(x != r && y != d)
                                    ksor ^= nimber[x + 1][r][d][y - 1];
                                vals.EB(ksor);
                            }
                    D << I(l) << I(r) << I(d) << I(u) << I(O(vals));
                    nimber[l][r][d][u] = mex(vals);
                }
    D << I(nimber);
    cout << (nimber[0][w - 1][0][h - 1] ? "First" : "Second") << nl;
 
}
