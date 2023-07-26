#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	auto random_vec = [](int n, int r) {
		vector<int> s(rd(1, n));
		for (auto& x : s)
			x = rd(0, r - 1);
		return s;
	};

	int r = rd(1, 26);
	auto s = random_vec(30, r);
	debug(r, s);
	int n = ssize(s);

	vector<vector<int>> trie = {vector(r, -1)};
	REP(i, n) {
		int v = 0;
		FOR(j, i, n - 1) {
			int c = s[j];
			if(trie[v][c] == -1) {
				int u = ssize(trie);
				trie[v][c] = u;
				trie.emplace_back(vector(r, -1));
				v = u;
			}
			else
				v = trie[v][c];
		}
	}
	debug(trie);

	SuffixTree tree(s, r);
	debug(tree.sons);

	function<void (int, int)> compare_trees = [&](int vtrie, int vsuff) {
		REP(c, r)
			assert(bool(trie[vtrie][c] == -1) == bool(tree.sons[vsuff].find(c) == tree.sons[vsuff].end()));
		REP(c, r)
			if(trie[vtrie][c] != -1) {
				vector<int> substr_trie = {c};
				int u = trie[vtrie][c];
				while(true) {
					int cnt_minusone = 0;
					REP(c2, r)
						if(trie[u][c2] == -1)
							++cnt_minusone;
					debug(u, cnt_minusone);
					if(cnt_minusone == r - 1) {
						REP(c2, r) {
							debug(u, c2);
							if(trie[u][c2] != -1) {
								substr_trie.emplace_back(c2);
								u = trie[u][c2];
								break;
							}
						}
					}
					else
						break;
				}

				vector<int> substr_tree;
				int usuff = tree.sons[vsuff][c];
				assert(tree.up_edge_range[usuff].first <= tree.up_edge_range[usuff].second);
				FOR(i, tree.up_edge_range[usuff].first, tree.up_edge_range[usuff].second)
					substr_tree.emplace_back(s[i]);

				debug(vtrie, c, substr_trie, u);
				debug(vsuff, c, substr_tree, usuff);
				assert(substr_trie == substr_tree);
				compare_trees(u, usuff);
			}
	};
	compare_trees(0, 0);


	/*
	SuffixTree tree(vector{0, 1, 0, 0, 1, -1}, 2);
	debug(tree.sons);
	debug(tree.up_edge_range);
	debug(tree.parent);
	debug(tree.slink);
	exit(0);
	*/
}
