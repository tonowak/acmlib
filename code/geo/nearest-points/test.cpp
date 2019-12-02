#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

bool test(int) {
	NearestPoints<15, 500> np;
	vector<P> pts;
	auto brute = [&](P p) {
		Double dst = -1; P curr;
		for(auto &q : pts) {
			Double _d = dist(p, q);
			if(dst == -1 || dst > _d) 
				dst = _d, curr = q;
		}
		return curr;
	};

	int n = 10000;
	REP(i, n) {
		P p(rd(-1e9, 1e9), rd(-1e9, 1e9));
		if(i < 1000 || rd(0, 1)) {
			pts.emplace_back(p);
			np.add(p);
		}
		else {
			np.query(p);
			//if(np.query(p) != brute(p)) 
				//return true;
		}
	}
	return false;
}
