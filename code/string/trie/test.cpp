#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	auto get_random_str = [&] {
		int len = rd(1, 4);
		string ret;
		while(len --> 0)
			ret += char('a' + rd(0, 2));
		return ret;
	};
	set<string> inside;
	Trie trie;
	while(ssize(inside) < n) {
		string s = get_random_str();
		inside.emplace(s);
		trie.add(s);
		debug(s.data());
	}
	while(n --> 0) {
		string s = get_random_str();
		bool is_inside = (inside.find(s) != inside.end());
		debug(s.data(), is_inside);
		assert(is_inside == trie.is_in_trie(s));
	}
}

