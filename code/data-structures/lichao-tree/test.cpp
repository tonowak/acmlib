#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 1000);
	int m = rd(1, 129);
	int range_values = 1000;
	LiChaoTree tree(m);
	vector<Function> functions(n);
	for(Function &f : functions) {
		f = Function{rd(range_values, range_values), rd(range_values, range_values)};
		tree.add_func(f);
	}
	int x = rd(0, m - 1);
	LL min_val = LL(1e18);
	for(Function &f : functions)
		min_val = min(min_val, f(x));
	assert(min_val == tree.get_min(x));
}
