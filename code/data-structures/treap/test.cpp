#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

vector<int> get_all_vals(Treap::pNode n) {
	vector<int> ret;
	if(n->l)
		ret = get_all_vals(n->l);
	ret.emplace_back(n->val);
	if(n->r)
		for(int val : get_all_vals(n->r))
			ret.emplace_back(val);
	return ret;
}

void test() {
	int n = rd(1, 10);
	Treap treap;
	vector<int> v;
	while(n --> 0) {
		int i = rd(0, ssize(v));
		int val = rd(-10, 10);
		v.insert(v.begin() + i, val);
		treap.insert(i, val);
		assert(v == get_all_vals(treap.root));
	}
}
