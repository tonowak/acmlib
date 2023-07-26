/*
 * Opis: O(n log n) lub O(n \alpha),
 * 	Dla słowa \texttt{abaab\#} (hash jest aby to zawsze liście były stanami kończącymi)
 * 	stworzy \texttt{sons[0]=\{(\#,10),(a,4),(b,8)\}, sons[4]=\{(a,5),(b,6)\}, sons[6]=\{(\#,7),(a,2)\}, sons[8]=\{(\#,9),(a,3)\}},
 * 	reszta sons'ów pusta, \texttt{slink[6]=8} i reszta slink'ów $0$
 * 	(gdzie slink jest zdefiniowany dla nie-liści jako wierzchołek zawierający ten suffix bez ostatniej literki),
 * 	\texttt{up\_edge\_range[2]=up\_edge\_range[3]=(2,5), up\_edge\_range[5]=(3,5)} i reszta jednoliterowa.
 * 	Wierzchołek 1 oraz suffix wierzchołków jest roboczy.
 * 	Zachodzi \texttt{up\_edge\_range[0]=(-1,-1), parent[0]=0, slink[0]=1}.
 */
struct SuffixTree {
	const int n;
	const vector<int> &_in;
	vector<map<int, int>> sons;
	vector<pair<int, int>> up_edge_range;
	vector<int> parent, slink;

	int tv = 0, tp = 0, ts = 2, la = 0;
	void ukkadd(int c) {
		auto &lr = up_edge_range;
suff:
		if (lr[tv].second < tp) {
			if (sons[tv].find(c) == sons[tv].end()) {
				sons[tv][c] = ts; lr[ts].first = la; parent[ts++] = tv;
				tv = slink[tv]; tp = lr[tv].second + 1; goto suff;
			}
			tv = sons[tv][c]; tp = lr[tv].first;
		}
		if (tp == -1 || c == _in[tp])
			tp++;
		else {
			lr[ts + 1].first = la; parent[ts + 1] = ts;
			lr[ts].first = lr[tv].first; lr[ts].second = tp - 1;
			parent[ts] = parent[tv]; sons[ts][c] = ts + 1; sons[ts][_in[tp]] = tv;
			lr[tv].first = tp; parent[tv] = ts;
			sons[parent[ts]][_in[lr[ts].first]] = ts; ts += 2;
			tv = slink[parent[ts - 2]]; tp = lr[ts - 2].first;
			while (tp <= lr[ts - 2].second) {
				tv = sons[tv][_in[tp]]; tp += lr[tv].second - lr[tv].first + 1;
			}
			if (tp == lr[ts - 2].second + 1)
				slink[ts - 2] = tv;
			else
				slink[ts - 2] = ts;
			tp = lr[tv].second - (tp - lr[ts-2].second) + 2; goto suff;
		}
	}

	// Remember to append string with a hash.
	SuffixTree(const vector<int> &in, int alpha)
		: n(ssize(in)), _in(in), sons(2 * n + 1),
		up_edge_range(2 * n + 1, pair(0, n - 1)), parent(2 * n + 1), slink(2 * n + 1) {
		up_edge_range[0] = up_edge_range[1] = {-1, -1};
		slink[0] = 1;
		// When changing map to vector, fill sons exactly here with -1 and replace if in ukkadd with sons[tv][c] == -1.
		REP(ch, alpha)
			sons[1][ch] = 0;
		for(; la < n; ++la)
			ukkadd(in[la]);
	}
};
