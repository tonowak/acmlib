/*
 * Opis: O(n + alpha),
 * $sa$ zawiera posortowane suffixy, zawiera pusty suffix,
 * $lcp[i]$ to $lcp$ suffixu $sa[i]$ i $sa[i + 1]$,
 * Dla \texttt{s = aabaaab}, \texttt{sa=\{7,3,4,0,5,1,6,2\},lcp=\{0,2,3,1,2,0,1\}}
 */
void induced_sort(const vector<int> &vec, int alpha, vector<int> &sa,
		const vector<bool> &sl, const vector<int> &lms_idx) {
	vector<int> l(alpha), r(alpha);
	for (int c : vec) {
		if (c + 1 < alpha)
			++l[c + 1];
		++r[c];
	}
	partial_sum(l.begin(), l.end(), l.begin());
	partial_sum(r.begin(), r.end(), r.begin());
	fill(sa.begin(), sa.end(), -1);
	for (int i = ssize(lms_idx) - 1; i >= 0; --i)
		sa[--r[vec[lms_idx[i]]]] = lms_idx[i];
	for (int i : sa)
		if (i >= 1 and sl[i - 1])
			sa[l[vec[i - 1]]++] = i - 1;
	fill(r.begin(), r.end(), 0);
	for (int c : vec)
		++r[c];
	partial_sum(r.begin(), r.end(), r.begin());
	for (int k = ssize(sa) - 1, i = sa[k]; k >= 1; --k, i = sa[k])
		if (i >= 1 and not sl[i - 1])
			sa[--r[vec[i - 1]]] = i - 1;
}
vector<int> sa_is(const vector<int> &vec, int alpha) {
	const int n = ssize(vec);
	vector<int> sa(n), lms_idx;
	vector<bool> sl(n);
	for (int i = n - 2; i >= 0; --i) {
		sl[i] = vec[i] > vec[i + 1] or (vec[i] == vec[i + 1] and sl[i + 1]);
		if (sl[i] and not sl[i + 1])
			lms_idx.emplace_back(i + 1);
	}
	reverse(lms_idx.begin(), lms_idx.end());
	induced_sort(vec, alpha, sa, sl, lms_idx);
	vector<int> new_lms_idx(ssize(lms_idx)), lms_vec(ssize(lms_idx));
	for (int i = 0, k = 0; i < n; ++i)
		if (not sl[sa[i]] and sa[i] >= 1 and sl[sa[i] - 1])
			new_lms_idx[k++] = sa[i];
	int cur = sa[n - 1] = 0;
	REP (k, ssize(new_lms_idx) - 1) {
		int i = new_lms_idx[k], j = new_lms_idx[k + 1];
		if (vec[i] != vec[j]) {
			sa[j] = ++cur;
			continue;
		}
		bool flag = false;
		for (int a = i + 1, b = j + 1;; ++a, ++b) {
			if (vec[a] != vec[b]) {
				flag = true;
				break;
			}
			if ((not sl[a] and sl[a - 1]) or (not sl[b] and sl[b - 1])) {
				flag = not (not sl[a] and sl[a - 1] and not sl[b] and sl[b - 1]);
				break;
			}
		}
		sa[j] = (flag ? ++cur : cur);
	}
	REP (i, ssize(lms_idx))
		lms_vec[i] = sa[lms_idx[i]];
	if (cur + 1 < ssize(lms_idx)) {
		vector<int> lms_sa = sa_is(lms_vec, cur + 1);
		REP (i, ssize(lms_idx))
			new_lms_idx[i] = lms_idx[lms_sa[i]];
	}
	induced_sort(vec, alpha, sa, sl, new_lms_idx);
	return sa;
}
vector<int> suffix_array(const vector<int> &s, int alpha) {
	vector<int> vec(ssize(s) + 1);
	REP(i, ssize(s))
		vec[i] = s[i] + 1;
	vector<int> ret = sa_is(vec, alpha + 2);
	return ret;
}
vector<int> get_lcp(const vector<int> &s, const vector<int> &sa) {
	int n = ssize(s), k = 0;
	vector<int> lcp(n), rank(n);
	REP (i, n)
		rank[sa[i + 1]] = i;
	for (int i = 0; i < n; i++, k ? k-- : 0) {
		if (rank[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = sa[rank[i] + 2];
		while (i + k < n and j + k < n and s[i + k] == s[j + k])
			k++;
		lcp[rank[i]] = k;
	}
	lcp.pop_back();
	lcp.insert(lcp.begin(), 0);
	return lcp;
}
