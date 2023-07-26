#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int limx = rd(1, 20);
	int limy = rd(1, 20);
	vector brute(limx, vector (limy, 0));
	Fenwick2d tree(limx);

	vector<pair<int,int>> points;
	const int sz = rd(0, 10);
	REP(i, sz) {
		points.emplace_back(rd(0, limx - 1), rd(0, limy - 1));
	}
	for (auto [x, y] : points)
		tree.preprocess(x, y);
	tree.init();

	REP(op, 20) {
		if(rd(0, 1) and sz) {
			int i = rd(0, sz - 1);
			auto [x, y] = points[i];
			int val = rd(-10, 10);
			tree.update(x, y, val);
			brute[x][y] += val;
		}
		else {
			int x = rd(0, limx - 1);
			int y = rd(0, limy - 1);
			LL sum = 0;
			FOR(i, 0, x)
				FOR(j, 0, y)
					sum += brute[i][j];
			assert(sum == tree.query(x, y));
		}
	}
}
