#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

stringstream wzorc(stringstream in) {
	stringstream out;

	int n, q;
	in >> n >> q;
	LinkCut tree(n);

	while(q --> 0) {
		int type;
		in >> type;
		if(type == 0) {
			int v, u;
			in >> v >> u;
			if(v == u or tree.is_in_same_tree(v, u))
				out << "0\n";
			else {
				out << "1\n";
				tree.link(v, u);
			}
		}
		else if(type == 1) {
			int v, u;
			in >> v >> u;
			if(v == u or not tree.is_in_same_tree(v, u))
				out << "0\n";
			else {
				out << "1\n";
				tree.cut(v, u);
			}
		}
		else if(type == 2) {
			int v, u;
			in >> v >> u;
			if(not tree.is_in_same_tree(v, u))
				out << "0\n";
			else
				out << "1 " << tree.dist(v, u) << '\n';
		}
		else if(type == 3) {
			int root, v, u;
			in >> root >> v >> u;
			if(not tree.is_in_same_tree(v, u) or not tree.is_in_same_tree(v, root))
				out << "0\n";
			else
				out << "1 " << tree.lca(root, v, u) << '\n';
		}
		else if(type == 4) {
			int v, val;
			in >> v >> val;
			tree.apply_on_vertex(v, [&](AdditionalInfo &info) {
					info.set_value(val);
					});
		}
		else if(type == 5) {
			int v, u;
			in >> v >> u;
			if(not tree.is_in_same_tree(v, u))
				out << "0\n";
			else
				out << "1 " << tree.get_path_sum(v, u) << '\n';
		}
		else if(type == 6) {
			int v, u;
			in >> v >> u;
			if(v == u or not tree.is_in_same_tree(v, u))
				out << "0\n";
			else
				out << "1 " << tree.get_subtree_sum(v, u) << '\n';
		}
		else if(type == 7) {
			int v, u, val;
			in >> v >> u >> val;
			if(not tree.is_in_same_tree(v, u))
				out << "0\n";
			else {
				tree.add_on_path(v, u, val);
				out << "1\n";
			}
		}
		else if(type == 8) {
			int v, u, val;
			in >> v >> u >> val;
			if(v == u or not tree.is_in_same_tree(v, u))
				out << "0\n";
			else {
				tree.add_on_subtree(v, u, val);
				out << "1\n";
			}
		}
	}
	return out;
}

stringstream brute(stringstream in) {
	stringstream out;

	int n, q;
	in >> n >> q;
	vector<vector<int>> graph(n);
	vector<int> node_value(n);

	auto is_in_same_tree = [&](int v, int u) -> bool {
		debug(v, u);
		vector<bool> vis(n, false);
		function<void (int, int)> dfs = [&](int x, int p) {
			vis[x] = true;
			for(int y : graph[x])
				if(y != p and not vis[y])
					dfs(y, x);
		};
		dfs(v, -1);
		debug(vis);
		return vis[u];
	};

	auto get_path = [&](int s, int t) {
		vector<int> path;
		function<bool (int, int)> dfs = [&](int v, int p) {
			path.emplace_back(v);
			if(v == t)
				return true;
			for(int u : graph[v])
				if(u != p)
					if(dfs(u, v))
						return true;
			path.pop_back();
			return false;
		};
		dfs(s, -1);
		assert(not path.empty());
		return path;
	};

	auto get_in_subtree = [&](int s, int outside) {
		vector<int> in_subtree;
		function<void (int, int)> dfs = [&](int x, int p) {
			in_subtree.emplace_back(x);
			for(int y : graph[x])
				if(y != p)
					dfs(y, x);
		};
		vector<int> good_vertices = {s};
		for(int u : graph[s]) {
			dfs(u, s);
			bool is_outside = false;
			for(int v_sub : in_subtree)
				if(v_sub == outside) {
					is_outside = true;
					break;
				}
			if(not is_outside)
				for(int v_sub : in_subtree)
					good_vertices.emplace_back(v_sub);
			in_subtree.clear();
		}
		return good_vertices;
	};

	while(q --> 0) {
		int type;
		in >> type;
		if(type == 0) {
			int v, u;
			in >> v >> u;
			if(is_in_same_tree(v, u))
				out << "0\n";
			else {
				out << "1\n";
				graph[v].emplace_back(u);
				graph[u].emplace_back(v);
			}
		}
		else if(type == 1) {
			int v, u;
			in >> v >> u;
			if(v == u or not is_in_same_tree(v, u))
				out << "0\n";
			else {
				out << "1\n";
				vector<bool> vis(n, false);
				function<void (int, int)> dfs = [&](int x, int p) {
					vis[x] = true;
					for(int y : graph[x])
						if(y != p and not vis[y])
							dfs(y, x);
				};
				int found = -1;
				for(int x : graph[v]) {
					dfs(x, v);
					if(vis[u]) {
						found = x;
						break;
					}
				}
				assert(found != -1);
				auto rm_directed_edge = [&](int x, int y) {
					for(int i = 0; i < ssize(graph[x]); ++i)
						if(graph[x][i] == y) {
							graph[x].erase(graph[x].begin() + i);
							return;
						}
					assert(false);
				};
				rm_directed_edge(v, found);
				rm_directed_edge(found, v);
			}
		}
		else if(type == 2) {
			int v, u;
			in >> v >> u;
			if(not is_in_same_tree(v, u))
				out << "0\n";
			else {
				function<int (int, int)> dfs = [&](int x, int p) {
					if(x == u)
						return 0;
					for(int y : graph[x])
						if(y != p) {
							int got = dfs(y, x);
							if(got != -1)
								return got + 1;
						}
					return -1;
				};
				out << "1 " << dfs(v, -1) << '\n';
			}
		}
		else if(type == 3) {
			int root, v, u;
			in >> root >> v >> u;
			if(not is_in_same_tree(v, u) or not is_in_same_tree(v, root))
				out << "0\n";
			else {
				vector<int> parent(n, -1), depth(n, 0);
				function<void (int, int)> dfs = [&](int x, int p) {
					parent[x] = p;
					for(int y : graph[x])
						if(y != p) {
							depth[y] = depth[x] + 1;
							dfs(y, x);
						}
				};
				dfs(root, -1);
				if(depth[v] < depth[u])
					swap(v, u);
				assert(depth[v] >= depth[u]);
				while(depth[v] > depth[u])
					v = parent[v];
				while(v != u) {
					v = parent[v];
					u = parent[u];
				}
				out << "1 " << v << '\n';
			}
		}
		else if(type == 4) {
			int v, val;
			in >> v >> val;
			node_value[v] = val;
		}
		else if(type == 5) {
			int v, u;
			in >> v >> u;
			if(not is_in_same_tree(v, u))
				out << "0\n";
			else {
				vector path = get_path(v, u);
				LL sum = 0;
				for(int w : path)
					sum += node_value[w];
				out << "1 " << sum << '\n';
			}
		}
		else if(type == 6) {
			int v, u;
			in >> v >> u;
			if(v == u or not is_in_same_tree(v, u))
				out << "0\n";
			else {
				LL sum = 0;
				for(int w : get_in_subtree(v, u))
					sum += node_value[w];
				out << "1 " << sum << '\n';
			}
		}
		else if(type == 7) {
			int v, u, val;
			in >> v >> u >> val;
			if(not is_in_same_tree(v, u))
				out << "0\n";
			else {
				vector path = get_path(v, u);
				for(int w : path)
					node_value[w] += val;
				out << "1\n";
			}
		}
		else if(type == 8) {
			int v, u, val;
			in >> v >> u >> val;
			if(v == u or not is_in_same_tree(v, u))
				out << "0\n";
			else {
				for(int w : get_in_subtree(v, u))
					node_value[w] += val;
				out << "1\n";
			}
		}
	}
	return out;
}

void test() {
	int n = rd(1, 20), q = rd(1, 10000);
	n = rd(1, n);
	stringstream out;
	out << n << ' ' << q << '\n';

	while(q --> 0) {
		int type = rd(0, 8);
		out << type << ' ';
		if(type == 0)
			out << rd(0, n - 1) << ' ' << rd(0, n - 1) << '\n';
		else if(type == 1)
			out << rd(0, n - 1) << ' ' << rd(0, n - 1) << '\n';
		else if(type == 2)
			out << rd(0, n - 1) << ' ' << rd(0, n - 1) << '\n';
		else if(type == 3)
			out << rd(0, n - 1) << ' ' << rd(0, n - 1) << ' ' << rd(0, n - 1) << '\n';
		else if(type == 4)
            out << rd(0, n - 1) << ' ' << rd(-100, 100) << '\n';
        else if(type == 5)
            out << rd(0, n - 1) << ' ' << rd(0, n - 1) << '\n';
		else if(type == 6)
            out << rd(0, n - 1) << ' ' << rd(0, n - 1) << '\n';
		else if(type == 7)
			out << rd(0, n - 1) << ' ' << rd(0, n - 1) << ' ' << rd(-100, 100) << '\n';
		else if(type == 8)
			out << rd(0, n - 1) << ' ' << rd(0, n - 1) << ' ' << rd(-100, 100) << '\n';
        else
			assert(false);
	}

	assert(wzorc(stringstream(out.str())).str() == brute(stringstream(out.str())).str());
}
