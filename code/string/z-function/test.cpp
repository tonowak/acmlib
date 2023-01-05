#include "../../utils/testing/test-wrapper.cpp"
#include "main.cpp"

void test() {
	int n = rd(1, 20);
	vector<int> s;
	REP(i, n)
		s.emplace_back(rd(0, 2));

	vector z_arr = get_z_function(s);
	REP(i, n) {
		int len;
		for(len = n - i; len >= 0; --len)
			if(vector(s.begin(), s.begin() + len) 
					== vector(s.begin() + i, s.begin() + i + len))
				break;
		assert(z_arr[i] == len);
	}
	assert(get_z_function(vector{0,1,0,0,1,0,1,0,0,1}) == (vector{10,0,1,3,0,5,0,1,2,0}));
}
