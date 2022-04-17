/*
 * Opis: Trie
 * Czas: O(n \log \alpha)
 * Użycie: Trie trie; trie.add(str);
 */

struct Trie {
	vector<unordered_map<char, int>> child = {{}};
	unordered_set<int> word_ends;
	int get_child(int v, char a) {
		if(child[v].find(a) == child[v].end()) {
			child[v][a] = ssize(child); 
			child.emplace_back();
		}
		return child[v][a];
	}
	void add(string word) {
		int v = 0;
		for(char c : word)
			v = get_child(v, c);
		word_ends.emplace(v);
	}
	bool is_in_trie(string word) {
		int v = 0;
		for(char c : word)
			if(child[v].find(c) == child[v].end())
				return false;
			else
				v = child[v][c];
		return word_ends.find(v) != word_ends.end();
	}
};
