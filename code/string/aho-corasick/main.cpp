/*
 * Opis: Template do Aho-Corasick
 * Czas: O(S \alpha)
 * Użycie:
 * 	Operuje na alfabecie od 0 do alpha - 1 (alpha ustawiamy ręcznie)
 * 	Konstruktor tworzy sam korzeń w v[0]
 * 	add(s) dodaje słowo s
 * 	convert() zamienia nieodwracalnie trie w automat Aho-Corasick
 * 	link(x) zwraca suffix link x
 * 	go(x, c) zwraca następnik x przez literę c
 * 	Generalnie najpierw dodajemy słowa, potem robimy convert(), a na koniec używamy go / link / cokolwiek sami dopiszemy
 */

const int alpha = 26; // rozmiar alfabetu
struct AhoCorasick {
	struct Node {
		array<int, alpha> next;
		int p;
		int pch;
		int link = -1;
		array<int, alpha> go;

		Node(int _p = -1, int ch = -1) : p(_p), pch(ch) {
			fill(next.begin(), next.end(), -1);
			fill(go.begin(), go.end(), -1);
		}
	};

	vector<Node> v;

	AhoCorasick() : v(1) {}
	bool converted = false;

	void add(const vector<int> &s) {
		assert(!converted);
		int x = 0;
		for (int c : s) {
			if (v[x].next[c] == -1) {
				v[x].next[c] = ssize(v);
				v.emplace_back(x, c);
			}
			x = v[x].next[c];
		}
	}

	int link(int x) {
		assert(converted);
		return v[x].link;
	}

	int go(int x, int c) {
		assert(converted);
		return v[x].go[c];
	}

	void convert() {
		assert(!converted);
		converted = true;
		queue<int> que;
		que.emplace(0);
		while (!que.empty()) {
			int x = que.front();
			que.pop();
			if (x == 0 || v[x].p == 0) {
				v[x].link = 0;
			}
			else {
				v[x].link = go(link(v[x].p), v[x].pch);
			}
			REP (c, alpha) {
				if (v[x].next[c] != -1) {
					v[x].go[c] = v[x].next[c];
					que.emplace(v[x].next[c]);
				}
				else {
					v[x].go[c] = x == 0 ? 0 : go(link(x), c);
				}
			}
		}
	}
};
