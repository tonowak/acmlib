/*
 * Opis: O(\log^2(mod)), dla pierwszego $mod$ znajduje generator modulo $mod$ (z być może sporą stałą).
 */

#include "../simple-modulo/main.cpp"
#include "../rho-pollard/main.cpp"

int primitive_root() {
	if(mod == 2)
		return 1;
	int q = mod - 1;
	vector<LL> v = factor(q);
	vector<int> fact;
	REP(i, ssize(v))
		if(!i or v[i] != v[i - 1])
			fact.emplace_back(v[i]);
	while(true) {
		int g = rd(2, q);
		auto is_good = [&] {
			for(auto &f : fact)
				if(powi(g, q / f) == 1)
					return false;
			return true;
		};
		if(is_good())
			return g;
	}
}
