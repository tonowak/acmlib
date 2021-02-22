/*
 * Opis: Trie
 * Czas: O(n \log \alpha)
 * Użycie: Trie trie; trie.add(str);
 */

struct Trie {
	vector<unordered_map<char, int>> child = {{}};
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
	}
};
