/*
 * Opis: O(N^3) (but fast in practice)
 *   Taken from: https://judge.yosupo.jp/submission/218005
 *   pdfcompile, weighted\_matching::init(n), weighted\_matching::add\_edge(a, b, c)
 *   vector<pii> temp, weighted\_matching::solve(temp).first
 */
#define pii pair<int, int>
namespace weighted_matching{
const int INF = (int)1e9 + 7;
const int MAXN = 1050; //double of possible N
struct E{
	int x, y, w;
};
int n, m;
E G[MAXN][MAXN];
int lab[MAXN], match[MAXN], slack[MAXN], st[MAXN], pa[MAXN], flo_from[MAXN][MAXN], S[MAXN], vis[MAXN];
vector<int> flo[MAXN];
queue<int> Q;

void init(int _n) {
	n = _n;
	for(int x = 1; x <= n; ++x)
		for(int y = 1; y <= n; ++y)
			G[x][y] = E{x, y, 0};
}

void add_edge(int x, int y, int w) {
	G[x][y].w = G[y][x].w = w;
}

int e_delta(E e) {
	return lab[e.x] + lab[e.y] - G[e.x][e.y].w * 2;
}
void update_slack(int u, int x) {
	if(!slack[x] || e_delta(G[u][x]) < e_delta(G[slack[x]][x]))
		slack[x] = u;
}
void set_slack(int x) {
	slack[x] = 0;
	for(int u = 1; u <= n; ++u)
		if(G[u][x].w > 0 && st[u] != x && S[st[u]] == 0)
			update_slack(u, x);
}
void q_push(int x) {
	if(x <= n) Q.push(x);
	else for(int i = 0; i < (int)flo[x].size(); ++i)
		q_push(flo[x][i]);
}
void set_st(int x, int b) {
	st[x] = b;
	if(x > n) for(int i = 0; i < (int)flo[x].size(); ++i)
		set_st(flo[x][i], b);
}
int get_pr(int b, int xr) {
	int pr = find(flo[b].begin(), flo[b].end(), xr) - flo[b].begin();
	if(pr & 1) {
		reverse(flo[b].begin() + 1, flo[b].end());
		return (int)flo[b].size() - pr;
	}
	else return pr;
}
void set_match(int x, int y) {
	match[x] = G[x][y].y;
	if(x <= n) return;
	E e = G[x][y];
	int xr = flo_from[x][e.x], pr = get_pr(x, xr);
	for(int i = 0; i < pr; ++i) set_match(flo[x][i], flo[x][i^1]);
	set_match(xr, y);
	rotate(flo[x].begin(), flo[x].begin() + pr, flo[x].end());
}
void augment(int x, int y) {
	while(1) {
		int ny = st[match[x]];
		set_match(x, y);
		if(!ny) return;
		set_match(ny, st[pa[ny]]);
		x = st[pa[ny]], y = ny;
	}
}
int get_lca(int x, int y) {
	static int t = 0;
	for(++t; x || y; swap(x, y)) {
		if(x == 0) continue;
		if(vis[x] == t) return x;
		vis[x] = t;
		x = st[match[x]];
		if(x) x = st[pa[x]];
	}
	return 0;
}
void add_blossom(int x, int l, int y) {
	int b = n + 1;
	while(b <= m && st[b]) ++b;
	if(b > m) ++m;
	lab[b] = 0, S[b] = 0;
	match[b] = match[l];
	flo[b].clear();
	flo[b].push_back(l);
	for(int u = x, v; u != l; u = st[pa[v]])
		flo[b].push_back(u), flo[b].push_back(v = st[match[u]]), q_push(v);
	reverse(flo[b].begin() + 1, flo[b].end());
	for(int u = y, v; u != l; u = st[pa[v]])
		flo[b].push_back(u), flo[b].push_back(v = st[match[u]]), q_push(v);
	set_st(b, b);
	for(int i = 1; i <= m; ++i) G[b][i].w = G[i][b].w = 0;
	for(int i = 1; i <= n; ++i) flo_from[b][i] = 0;
	for(int i = 0; i < (int)flo[b].size(); ++i) {
		int us = flo[b][i];
		for(int u = 1; u <= m; ++u)
			if(G[b][u].w == 0 || e_delta(G[us][u]) < e_delta(G[b][u]))
				G[b][u] = G[us][u], G[u][b] = G[u][us];
		for(int u = 1; u <= n; ++u)
			if(flo_from[us][u])
				flo_from[b][u] = us;
	}
	set_slack(b);
}
void expand_blossom(int b) {
	for(int i = 0; i < (int)flo[b].size(); ++i)
		set_st(flo[b][i], flo[b][i]);
	int xr = flo_from[b][G[b][pa[b]].x], pr = get_pr(b, xr);
	for(int i = 0; i < pr; i += 2) {
		int xs = flo[b][i], xns = flo[b][i + 1];
		pa[xs] = G[xns][xs].x;
		S[xs] = 1, S[xns] = 0;
		slack[xs] = 0, set_slack(xns);
		q_push(xns);
	}
	S[xr] = 1, pa[xr] = pa[b];
	for(int i = pr + 1; i < (int)flo[b].size(); ++i) {
		int xs = flo[b][i];
		S[xs] = -1, set_slack(xs);
	}
	st[b] = 0;
}
bool on_found_edge(E e) {
	int x = st[e.x], y = st[e.y];
	if(S[y] == -1) {
		pa[y] = e.x, S[y] = 1;
		int ny = st[match[y]];
		slack[y] = slack[ny] = 0;
		S[ny] = 0, q_push(ny);
	}
	else if(S[y] == 0) {
		int l = get_lca(x, y);
		if(!l) return augment(x, y), augment(y, x), true;
		else add_blossom(x, l, y);
	}
	return false;
}
bool matching() {
	fill(S + 1, S + m + 1, -1);
	fill(slack + 1, slack + m + 1, 0);
	Q = queue<int>();
	for(int x = 1; x <= m; ++x)
		if(st[x] == x && !match[x]) pa[x] = 0, S[x] = 0, q_push(x);
	if(Q.empty()) return false;
	while(1) {
		while(Q.size()) {
			int x = Q.front(); Q.pop();
			if(S[st[x]] == 1) continue;
			for(int y = 1; y <= n; ++y) {
				if(G[x][y].w > 0 && st[x] != st[y]) {
					if(e_delta(G[x][y]) == 0) {
						if(on_found_edge(G[x][y])) return true;
					}
					else update_slack(x, st[y]);
				}
			}
		}
		int d = INF;
		for(int b = n + 1; b <= m; ++b)
			if(st[b] == b && S[b] == 1) d = min(d, lab[b] / 2);
		for(int x = 1; x <= m; ++x)
			if(st[x] == x && slack[x]) {
				if(S[x] == -1) d = min(d, e_delta(G[slack[x]][x]));
				else if(S[x] == 0) d = min(d, e_delta(G[slack[x]][x]) / 2);
			}
		for(int x = 1; x <= n; ++x) {
			if(S[st[x]] == 0) {
				if(lab[x] <= d) return 0;
				lab[x] -= d;
			}
			else if(S[st[x]] == 1) lab[x] += d;
		}
		for(int b = n + 1; b <= m; ++b)
			if(st[b] == b) {
				if(S[st[b]] == 0) lab[b] += d * 2;
				else if(S[st[b]] == 1) lab[b] -= d * 2;
			}
		Q = queue<int>();
		for(int x = 1; x <= m; ++x)
			if(st[x] == x && slack[x] && st[slack[x]] != x && e_delta(G[slack[x]][x]) == 0)
				if(on_found_edge(G[slack[x]][x])) return true;
		for(int b = n + 1; b <= m; ++b)
			if(st[b] == b && S[b] == 1 && lab[b] == 0)
				expand_blossom(b);
	}
	return false;
}
pair<ll, int> solve(vector<pii> &ans) {
	fill(match + 1, match + n + 1, 0);
	m = n;
	int cnt = 0; LL sum = 0;
	for(int u = 0; u <= n; ++u) st[u] = u, flo[u].clear();
	int mx = 0;
	for(int x = 1; x <= n; ++x)
		for(int y = 1; y <= n; ++y){
			flo_from[x][y] = (x == y ? x : 0);
			mx = max(mx, G[x][y].w);
		}
	for(int x = 1; x <= n; ++x) lab[x] = mx;
	while(matching()) ++cnt;
	for(int x = 1; x <= n; ++x)
		if(match[x] && match[x] < x) {
			sum += G[x][match[x]].w;
			ans.push_back({x, G[x][match[x]].y});
		}
	return {sum, cnt};
}
}
