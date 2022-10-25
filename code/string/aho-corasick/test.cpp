#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"


void test() {
	int str_cnt = rd(0, 10);
	int queries = rd(0, 100);
	constexpr int max_len_str = 10;

	AhoCorasick aho;

	auto is_lit_on_link_path = [&](vector<bool> is_lit) {
		deque<int> que = {0};
		while (not que.empty()) {
			int v = que.front();
			que.pop_front();
			debug(v, is_lit[v], aho.link(v), is_lit[aho.link(v)]);
			is_lit[v] = is_lit[v] or (v != 0 and is_lit[aho.link(v)]);
			REP(c, alpha)
				if(aho.node[v].next[c] != -1)
					que.emplace_back(aho.node[v].next[c]);
		}
		return is_lit;
	};

	vector<vector<int>> patterns;
	while(str_cnt --> 0) {
		vector<int> pattern(rd(1, max_len_str));
		for(int &c : pattern)
			c = rd(0, alpha - 1);
		patterns.emplace_back(pattern);
		aho.add(pattern);
	}
	debug(patterns);
	aho.convert();
	
	auto is_suffix_equal_to_pattern = [&](vector<int> text) {
		REP(i, ssize(text)) {
			vector<int> suffix(text.begin() + i, text.end());
			for(auto &pattern : patterns)
				if(suffix == pattern)
					return true;
		}
		return false;
	};

	vector<bool> is_suffix_end(ssize(aho.node));
	REP(i, ssize(is_suffix_end))
		is_suffix_end[i] = aho.node[i].is_word_end;
	is_suffix_end = is_lit_on_link_path(is_suffix_end);
	debug(is_suffix_end);

	while(queries --> 0) {
		vector<int> text(rd(1, max_len_str));
		for(int &c : text)
			c = rd(0, alpha - 1);

		int v = 0;
		REP(i, ssize(text)) {
			vector<int> text_sub(text.begin(), text.begin() + i + 1);
			v = aho.go(v, text[i]);
			debug(i, text_sub, is_suffix_equal_to_pattern(text_sub), v);
			assert(is_suffix_end[v] == is_suffix_equal_to_pattern(text_sub));
		}
	}
}
