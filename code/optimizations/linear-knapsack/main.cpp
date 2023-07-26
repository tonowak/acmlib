/*
 * Opis: O(n\cdot\max(w_i)) zamiast typowego O(n\cdot\sum(w_i)), pamięć O(n+\max(w_i)),
 *   plecak zwracający największą otrzymywalną sumę ciężarów \texttt{<= bound}.
 */

LL knapsack(vector<int> w, LL bound) {
	erase_if(w, [=](int x){ return x > bound; });
	{
		LL sum = accumulate(w.begin(), w.end(), 0LL);
		if(sum <= bound)
			return sum;
	}
	LL w_init = 0;
	int b;
	for(b = 0; w_init + w[b] <= bound; ++b)
		w_init += w[b];

	int W = *max_element(w.begin(), w.end());
	vector<int> prev_s(2 * W, -1);
	auto get = [&](vector<int> &v, LL i) -> int& {
		return v[i - (bound  - W + 1)];
	};
	for(LL mu = bound + 1; mu <= bound + W; ++mu)
		get(prev_s, mu) = 0;
	get(prev_s, w_init) = b;
	FOR(t, b, ssize(w) - 1) {
		vector curr_s = prev_s;
		for(LL mu = bound - W + 1; mu <= bound; ++mu)
			get(curr_s, mu + w[t]) = max(get(curr_s, mu + w[t]), get(prev_s, mu));
		for(LL mu = bound + w[t]; mu >= bound + 1; --mu)
			for(int j = get(curr_s, mu) - 1; j >= get(prev_s, mu); --j)
				get(curr_s, mu - w[j]) = max(get(curr_s, mu - w[j]), j);
		swap(prev_s, curr_s);
	}
	for(LL mu = bound; mu >= 0; --mu)
		if(get(prev_s, mu) != -1)
			return mu;
	assert(false);
}
