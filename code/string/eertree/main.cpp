/*
 * Opis: O(n\alpha) konstrukcja, O(n) DP oraz odzyskanie.
 * Eertree ma korzeń ,,pusty'' w $0$ oraz ,,ujemny'' w $1$.
 * Z wierzchołka wychodzi krawędź z literą, gdy jego słowo można otoczyć z obu stron tą literą.
 * Funkcja \texttt{add} zwraca wierzchołek odpowiadający za największy palindromiczny suffix aktualnego słowa.
 * Suffix link prowadzi do najdłuższego palindromicznego suffixu słowa wierzchołka.
 * Linki tworzą drzewo z $1$ jako korzeń (który ma syna $0$).
 * Żeby policzyć liczbę wystąpień wierzchołka, po każdym dodaniu litery ,,wystarczy'' dodać $+1$ każdemu na ścieżce od \texttt{last} do korzenia po linkach.
 * \texttt{palindromic\_split\_dp} zwraca na każdym prefixie (min podział palindromiczny,
 * liczbę podziałów, indeks do odzyskania min podziału).
 * Gdy \texttt{only\_even\_lens} to może nie istnieć odpowiedź, wtedy \texttt{.mn == n + 1, .cnt == 0}.
 * \texttt{construct\_min\_palindromic\_split} zwraca palindromiczne przedziały pokrywające słowo.
 */
// BEGIN HASH
constexpr int alpha = 26;
struct Eertree {
	vector<array<int, alpha>> edge;
	array<int, alpha> empty;
	vector<int> str = {-1}, link = {1, 0}, len = {0, -1};
	int last = 0;
	Eertree() {
		empty.fill(0);
		edge.resize(2, empty);
	}
	int find(int v) {
		while(str[ssize(str) - 1] != str[ssize(str) - len[v] - 2])
			v = link[v];
		return v;
	}
	int add(int c) {
		str.emplace_back(c);
		last = find(last);
		if(edge[last][c] == 0) {
			edge.emplace_back(empty);
			len.emplace_back(len[last] + 2);
			link.emplace_back(edge[find(link[last])][c]);
			edge[last][c] = ssize(edge) - 1;
		}
		return last = edge[last][c];
	}
}; // END HASH
int add(int a, int b) { return a + b; }
// BEGIN HASH
struct Dp { int mn, mn_i, cnt; };
Dp operator+(Dp l, Dp r) {
	return {min(l.mn, r.mn), l.mn < r.mn ? l.mn_i : r.mn_i, add(l.cnt, r.cnt)};
}
vector<Dp> palindromic_split_dp(vector<int> str, bool only_even_lens = false) {
	int n = ssize(str);
	Eertree t;
	vector<int> big_link(2), diff(2);
	vector<Dp> series_ans(2), ans(n, {n + 1, -1, 0});
	REP(i, n) {
		int last = t.add(str[i]);
		if(last >= ssize(big_link)) {
			diff.emplace_back(t.len.back() - t.len[t.link.back()]);
			big_link.emplace_back(diff.back() == diff[t.link.back()] ? big_link[t.link.back()] : t.link.back());
			series_ans.emplace_back();
		}
		for(int v = last; t.len[v] > 0; v = big_link[v]) {
			int j = i - t.len[big_link[v]] - diff[v];
			series_ans[v] = j == -1 ? Dp{0, j, 1} : Dp{ans[j].mn, j, ans[j].cnt};
			if(diff[v] == diff[t.link[v]])
				series_ans[v] = series_ans[v] + series_ans[t.link[v]];
			if(i % 2 == 1 or not only_even_lens)
				ans[i] = ans[i] + Dp{series_ans[v].mn + 1, series_ans[v].mn_i, series_ans[v].cnt};
		}
	}
	return ans;
} // END HASH
// BEGIN HASH
vector<pair<int, int>> construct_min_palindromic_split(vector<Dp> ans) {
	if(ans.back().mn == ssize(ans) + 1)
		return {};
	vector<pair<int, int>> split = {{0, ssize(ans) - 1}};
	while(ans[split.back().second].mn_i != -1)
		split.emplace_back(0, ans[split.back().second].mn_i);
	reverse(split.begin(), split.end());
	REP(i, ssize(split) - 1)
		split[i + 1].first = split[i].second + 1;
	return split;
} // END HASH

