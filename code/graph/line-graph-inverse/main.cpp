/*
 * Opis: O((n+m)(\log n + 2^6)), dla danego H szuka takiego G, że L(G) = H,
 *   gdzie L to proces tworzenia line graph'a 
 *   -- z każdej krawędzi jest tworzony wierzchołek 
 *   i między daną parą takich wierzchołków jest krawędź,
 *   gdy krawędzie, na których leżą te wierzchołki, 
 *   mają wspólny wierzchołek.
 *   Funkcja zwraca informację o istnieniu przynajmniej
 *   jednego rozwiązania oraz przykładowe rozwiązanie,
 *   tzn. dla każdego wierzchołka line graphu wyznacza krawędź
 *   oryginalnego grafu, na której powinien leżeć.
 *   W skrócie, każde dwa nieizomorficzne spójne grafy proste 
 *   o przynajmniej pięciu wierzchołkach mają różne line graphy.
 *   Algorytm brutuje pasujący graf, aż będzie mieć wystarczający rozmiar,
 *   po czym dla nowych line graphowych wierzchołków
 *   wyznacza zbiór wierzchołków oryginalnego grafu,
 *   które są końcami krawędzi, których wierzchołki line graphu
 *   sąsiadują z rozpatrywanym wierzchołkiem,
 *   i wyznacza ich vertex cover. Jeżeli ma on rozmiar 2,
 *   to jest dodawana krawędź między nimi, a jeżeli 1,
 *   to jest tworzony nowy wierzchołek i dodawana krawędź.
 *   Ważne też jest, aby zapewnić, żeby konstruowany oryginalny graf
 *   nie musiał zawierać multikrawędzi.
 */

pair<bool, vector<pair<int, int>>> get_original_graph(int line_n, vector<pair<int, int>> line_edges) {
	vector<vector<int>> line_graph(line_n);
	for(auto &[v, u] : line_edges) {
		line_graph[v].emplace_back(u);
		line_graph[u].emplace_back(v);
	}

	map<vector<int>, int> line_neighbors_repeated;
	vector<int> line_vertex_reduced_to(line_n, -1);
	REP(v, line_n) {
		auto neigh_with_v = line_graph[v];
		neigh_with_v.emplace_back(v);
		sort(neigh_with_v.begin(), neigh_with_v.end());
		if(line_neighbors_repeated.find(neigh_with_v) == line_neighbors_repeated.end())
			line_neighbors_repeated[neigh_with_v] = v;
		else
			line_vertex_reduced_to[v] = line_neighbors_repeated[neigh_with_v];
	}

	vector<pair<int, int>> ans(line_n, pair(-1, -1));
	vector<bool> visited(line_n, false);
	REP(v, line_n)
		if(line_vertex_reduced_to[v] != -1)
			visited[v] = true;

	int og_cnt_fixed_v = 0;
	map<int, int> og_deg_visited;
	set<pair<int, int>> og_used_edges;

	auto save_edge = [&](int line_v) {
		assert(ans[line_v].first != -1);
		int v = ans[line_v].first;
		int u = ans[line_v].second;
		for(int og_v : {v, u})
			og_deg_visited[og_v] += 1;
		og_used_edges.emplace(min(v, u), max(v, u));
	};

	REP(component_v, line_n)
		if(not visited[component_v]) {
			vector<vector<int>> que_i_to_visited_neighbors;
			int og_n = 0;

			vector<int> que = {component_v};
			visited[component_v] = true;

			auto save_current_graph = [&](int until_i) {
				og_cnt_fixed_v += og_n;
				REP(que_j, until_i + 1)
					save_edge(que[que_j]);
			};

			REP(que_i, ssize(que)) {
				int line_v = que[que_i];
				for(int u : line_graph[line_v])
					if(not visited[u]) {
						visited[u] = true;
						que.emplace_back(u);
					}

				que_i_to_visited_neighbors.emplace_back();
				map<int, int> og_deg_near_v_line;
				for(int line_u : line_graph[line_v])
					if(ans[line_u] != pair(-1, -1)) {
						for(int og_u : {ans[line_u].first, ans[line_u].second})
							og_deg_near_v_line[og_u] += 1;
						que_i_to_visited_neighbors[que_i].emplace_back(line_u);
					}

				if(og_n <= 4) {
					function<bool (int, int, set<pair<int, int>>&)> backtrack
							= [&](int new_og_n, int i, set<pair<int, int>> &used_edges) {
						if(i == que_i + 1)
							return true;
						REP(v, new_og_n)
							FOR(u, v + 1, new_og_n - 1)
								if(used_edges.find(pair(v, u)) == used_edges.end()) {
									ans[que[i]] = {
										og_cnt_fixed_v + v,
										og_cnt_fixed_v + u
									};
									auto is_valid = [&] {
										REP(j, i) {
											bool should_be_neighbor_to_v = bool(
													find(que_i_to_visited_neighbors[i].begin(),
														 que_i_to_visited_neighbors[i].end(),
														 que[j])
													!=   que_i_to_visited_neighbors[i].end()
											);
											bool is_neighbor_to_v = [&] {
												auto [a, b] = ans[que[i]];
												auto [x, y] = ans[que[j]];
												return a == x or a == y or b == x or b == y;
											}();
											if(is_neighbor_to_v != should_be_neighbor_to_v)
												return false;
										}
										return true;
									};
									if(is_valid()) {
										used_edges.emplace(v, u);
										if(backtrack(new_og_n, i + 1, used_edges))
											return true;
										used_edges.erase(pair(v, u));
									}
								}
						return false;
					};

					og_n = [&] {
						for(int ret = 2; ret <= 8; ++ret) {
							set<pair<int, int>> used_edges;
							if(backtrack(ret, 0, used_edges))
								return ret;
						}
						return 9;
					}();

					if(og_n == 9)
						return {false, {}};
					if(og_n > 4)
						save_current_graph(que_i);
				}
				else {
					set<int> candidates;
					for(auto [og_v, deg] : og_deg_near_v_line)
						if(deg == og_deg_visited[og_v])
							candidates.emplace(og_v);

					auto get_best_cover = [&] {
						pair<int, int> found_cover_2 = {-1, -1};

						for(int og_v_cover0 : {
								ans[que_i_to_visited_neighbors[que_i].front()].first,
								ans[que_i_to_visited_neighbors[que_i].front()].second,
							})
							if(candidates.count(og_v_cover0)) {
								map<int, int> og_deg_uncovered;
								int uncovered = 0;
								for(int line_u : que_i_to_visited_neighbors[que_i]) {
									auto [og_v, og_u] = ans[line_u];
									if(og_v != og_v_cover0 and og_u != og_v_cover0) {
										++uncovered;
										for(int v : {og_v, og_u})
											++og_deg_uncovered[v];
									}
								}

								if(uncovered == 0)
									return make_tuple(1, og_v_cover0, -1);

								for(auto [og_v_cover1, og_deg_cover1] : og_deg_uncovered)
									if(candidates.count(og_v_cover1)
											and not og_used_edges.count(pair(
													min(og_v_cover0, og_v_cover1),
													max(og_v_cover0, og_v_cover1)
												))
											and og_deg_cover1 == uncovered)
										found_cover_2 = {og_v_cover0, og_v_cover1};
							}
						return make_tuple(found_cover_2.first == -1 ? 3 : 2,
								found_cover_2.first, found_cover_2.second);
					};
					auto [cover_size, og_v_cover0, og_v_cover1] = get_best_cover();
					if(cover_size == 3)
						return {false, {}};
					if(cover_size == 1) {
						og_v_cover1 = og_cnt_fixed_v++;
						og_n++;
					}
					ans[line_v] = {min(og_v_cover0, og_v_cover1), max(og_v_cover0, og_v_cover1)};
					save_edge(line_v);
				}
			}
			if(og_n <= 4)
				save_current_graph(ssize(que) - 1);
		}

	REP(line_v, line_n)
		if(line_vertex_reduced_to[line_v] != -1)
			ans[line_v] = ans[line_vertex_reduced_to[line_v]];

	return {true, ans};
}
