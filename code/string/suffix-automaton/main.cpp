/*
 * Opis: O(n\alpha) (szybsze, ale więcej pamięci) albo O(n\log\alpha) (mapa),
 *   buduje suffix automaton. Wystąpienia wzorca, liczba różnych podsłów, sumaryczna długość wszystkich podsłów,
 *   leksykograficznie $k$-te podsłowo, najmniejsze przesunięcie cykliczne, liczba wystąpień podsłowa, pierwsze wystąpienie,
 *   najkrótsze niewystępujące podsłowo, longest common substring wielu słów.
 */
struct SuffixAutomaton {
	static constexpr int sigma = 26;
	using Node = array<int, sigma>; // map<int, int>
	Node new_node;
	vector<Node> edges;
	vector<int> link = {-1}, length = {0};
	int last = 0;
	SuffixAutomaton() {
		new_node.fill(-1);	 // -1 - stan nieistniejacy
		edges = {new_node};  // dodajemy stan startowy, ktory reprezentuje puste slowo
	}
			
	void add_letter(int c) {
		edges.emplace_back(new_node);
		length.emplace_back(length[last] + 1);
		link.emplace_back(0);
		int r = ssize(edges) - 1, p = last;
		while(p != -1 && edges[p][c] == -1) {
			edges[p][c] = r;
			p = link[p];
		}
		if(p != -1) {
			int q = edges[p][c];
			if(length[p] + 1 == length[q])
				link[r] = q;
			else {
				edges.emplace_back(edges[q]);
				length.emplace_back(length[p] + 1);
				link.emplace_back(link[q]);
				int q_prim = ssize(edges) - 1;
				link[q] = link[r] = q_prim;
				while(p != -1 && edges[p][c] == q) {
					edges[p][c] = q_prim;
					p = link[p];
				}
			}
		}
		last = r;
	}
	bool is_inside(vector<int> &s) {
		int q = 0;
		for(int c : s) {
			if(edges[q][c] == -1)
				return false;
			q = edges[q][c];
		}
		return true;
	}
};
