/*
 * Opis: O(q \log^2 n), rozwala zadania, gdzie wynik to dp bottom-up na drzewie i zmienia się wartość wierzchołka/krawędzi.
 * To zakłada, że da się tak uogólnić tego bottom-up'a, że da się trzymać fragmenty drzewa
 * z "dwoma dziurami" i doczepiać jak LEGO dwa takie fragmenty do siebie.
 */
#include "../hld/main.cpp"
// Information about a single vertex (e.g. color).
// A component contains answers for vertices, not edges.
using Value_v = int;
// Probably you want: some information about the up vertex, the down vertex,
// answer for whole component, answer containing up, answer containing down, 
// answer containing both up and down.
struct DpTwoEnds;
// Merge two disjoint-vertex paths. Assume that there is an edge
// between "up" vertex of d and "down" vertex od u.
DpTwoEnds merge(DpTwoEnds u, DpTwoEnds d);
// DpOneEnd Contains information about a component after forgetting the "down" vertex.
// Probably you want: answer for whole component, informations about top vertices.
// It needs a default constructor.
struct DpOneEnd;
// Merge two parallel components. They are vertex-disjoint. They do not contain the
// parent (it will be included in the next function).
DpOneEnd merge(DpOneEnd a, DpOneEnd b);
// Assuming that DpOneEnd contain all components of the light sons of the parent,
// merge those components once with the parent. It has to support passing the
// default/neutral value of DpOneEnd -- it means that the vertex doesn't have light sons.
DpTwoEnds merge(DpOneEnd sons, Value_v value_parent);
// From a path that remembers "up" and "down" vertices, forget the "down" one.
DpOneEnd two_to_one(DpTwoEnds two);

template<class T> struct Tree {
	int leaves = 1;
	vector<T> tree;
	Tree(int n = 0) {
		while(leaves < n)
			leaves *= 2;
		tree.resize(2 * leaves);
	}
	void set(int i, T t) {
		tree[i += leaves] = t;
		while(i /= 2)
			tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
	}
	T get() { return tree[1]; }
};
struct DpDynamicBottomUp {
	int n;
	HLD hld;
	vector<Tree<DpOneEnd>> tree_sons;
	vector<Tree<DpTwoEnds>> tree_path;
	vector<Value_v> current_values;
	vector<int> which_on_path, which_light_son;
	DpDynamicBottomUp(vector<vector<int>> graph, vector<Value_v> initial_values)
		: n(ssize(graph)), hld(n, graph), tree_sons(n), tree_path(n), current_values(initial_values), which_on_path(n, -1), which_light_son(n, -1) {
		function<void (int, int*)> dfs = [&](int v, int *on_heavy_cnt) {
			int light_sons_cnt = 0, tmp = 0;
			which_on_path[v] = (*(on_heavy_cnt = on_heavy_cnt ?: &tmp))++;
			for(int u : hld.adj[v])
				if(u != hld.par[v])
					dfs(u, hld.nxt[u] == u ? which_light_son[u] = light_sons_cnt++, nullptr : on_heavy_cnt);
			tree_sons[v] = Tree<DpOneEnd>(light_sons_cnt);
			tree_path[v] = Tree<DpTwoEnds>(tmp);
		};
		dfs(0, 0);
		REP(v, n)
			set(v, initial_values[v]);
	}
	void set(int v, int value_vertex) {
		current_values[v] = value_vertex;
		while(true) {
			tree_path[hld.nxt[v]].set(which_on_path[v], merge(tree_sons[v].get(), current_values[v]));
			v = hld.nxt[v];
			if(hld.par[v] == -1)
				break;
			tree_sons[hld.par[v]].set(which_light_son[v], two_to_one(tree_path[hld.nxt[v]].get()));
			v = hld.par[v];
		}
	}
	DpTwoEnds get() { return tree_path[0].get(); }
};
