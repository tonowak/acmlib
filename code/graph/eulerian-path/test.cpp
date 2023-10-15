#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	constexpr int N = 4, M = 8;
	int n = rd(2, N);
	const bool bidirectional = rd(0, 1);
	int m = rd(n - 1 + n / 2, M);

	vector<vector<PII>> graph(n);
	int edge_count = 0;

	vector<int> in(n);
	auto add_edge = [&](int a, int b) {
		graph[a].emplace_back(b, edge_count);
		if(bidirectional)
			graph[b].emplace_back(a, edge_count);
		else
			in[b]++;
		edge_count++;
	};

	FOR(i, 1, n - 1) {
		int a = i;
		int b = rd(0, i - 1);
		if(rd(0, 1)) swap(a, b);
		add_edge(a, b);
	}

	auto gen_second = [&](int a) {
		int b = rd(0, n - 2);
		if(a <= b) b++;
		return b;
	};

	while(edge_count < m) {
		if(bidirectional) {
			vector<int> cands;
			REP(i, n)
				if(ssize(graph[i]) % 2)
					cands.emplace_back(i);

			assert(ssize(cands) % 2 == 0);

			if(cands.empty()) {
				int a = rd(0, n - 1);
				int b = gen_second(a);
				cands = {a, b};
			}

			shuffle(cands.begin(), cands.end(), tester_rng);
			int a = cands[0], b = cands[1];
			add_edge(a, b);
		} else {
			vector<int> cands_in, cands_out;
			REP(i, n) {
				if(ssize(graph[i]) < in[i])
					cands_out.emplace_back(i);
				else if(ssize(graph[i]) > in[i])
					cands_in.emplace_back(i);
			}

			if(cands_in.empty()) {
				int a = rd(0, n - 1);
				int b = gen_second(a);
				if(rd(0, 1)) swap(a, b);
				cands_out = {a}, cands_in = {b};
			}

			shuffle(cands_out.begin(), cands_out.end(), tester_rng);
			shuffle(cands_in.begin(), cands_in.end(), tester_rng);
			int a = cands_out[0], b = cands_in[0];
			add_edge(a, b);
		}
	}

	int too_small = 0, too_big = 0;
	REP(i, n) {
		if(bidirectional && ssize(graph[i]) % 2) {
			if(!too_small) too_small++;
			else too_big++;
		}
		else if(!bidirectional) {
			if(abs(ssize(graph[i]) - in[i]) > 1) {
				too_big = 2;
			} else if(ssize(graph[i]) < in[i]) {
				too_small++;
			} else if(ssize(graph[i]) > in[i]) {
				too_big++;
			}
		}
	}

	if(too_small > 1 || too_big > 1 || too_small != too_big) {
		assert(EulerianPath(graph, !bidirectional).path.empty());
		return;
	}

	set<tuple<int, int, int>> edges;
	REP(i, n) for(auto &[j, id] : graph[i])
		edges.emplace(i, j, id);

	auto remove_edge = [&](int a, int b) {
		auto it = edges.lower_bound({a, b, 0});
		assert(it != edges.end());
		auto [x, y, z] = *it;
		assert(x == a && y == b);
		edges.erase(it);
		if(bidirectional)
			edges.erase(tuple{b, a, z});
	};

	auto path = EulerianPath(graph, !bidirectional).path;

	REP(i, ssize(path) - 1)
		remove_edge(path[i], path[i + 1]);

	assert(edges.empty());
}
