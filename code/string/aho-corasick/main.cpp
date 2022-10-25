/*
 * Opis: Template do Aho-Corasick
 * Czas: O(S \alpha)
 * Użycie:
 * 	Operuje na alfabecie od 0 do alpha - 1 (alpha ustawiamy ręcznie)
 * 	Konstruktor tworzy sam korzeń w node[0]
 * 	add(s) dodaje słowo s
 * 	convert() zamienia nieodwracalnie trie w automat Aho-Corasick
 * 	link(x) zwraca suffix link x
 * 	go(x, c) zwraca następnik x przez literę c
 * 	Najpierw dodajemy słowa, potem robimy convert(), a na koniec używamy go i link
 */

constexpr int alpha = 26;
struct AhoCorasick {
	struct Node {
		array<int, alpha> next, go;
		int p, pch, link = -1;
		bool is_word_end = false;

		Node(int _p = -1, int ch = -1) : p(_p), pch(ch) {
			fill(next.begin(), next.end(), -1);
			fill(go.begin(), go.end(), -1);
		}
	};
	vector<Node> node;
	bool converted = false;

	AhoCorasick() : node(1) {}

	void add(const vector<int> &s) {
		assert(!converted);
		int v = 0;
		for (int c : s) {
			if (node[v].next[c] == -1) {
				node[v].next[c] = ssize(node);
				node.emplace_back(v, c);
			}
			v = node[v].next[c];
		}
		node[v].is_word_end = true;
	}

	int link(int v) {
		assert(converted);
		return node[v].link;
	}

	int go(int v, int c) {
		assert(converted);
		return node[v].go[c];
	}

	void convert() {
		assert(!converted);
		converted = true;
		deque<int> que = {0};
		while (not que.empty()) {
			int v = que.front();
			que.pop_front();
			if (v == 0 or node[v].p == 0)
				node[v].link = 0;
			else
				node[v].link = go(link(node[v].p), node[v].pch);
			REP (c, alpha) {
				if (node[v].next[c] != -1) {
					node[v].go[c] = node[v].next[c];
					que.emplace_back(node[v].next[c]);
				}
				else
					node[v].go[c] = v == 0 ? 0 : go(link(v), c);
			}
		}
	}
};
