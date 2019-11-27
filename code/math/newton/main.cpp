struct Newton {
	vector<MI> fac, rev;
	Newton(int n) {
		fac = rev = vector<MI>(n + 1, 1);
		FOR(i, 1, n) fac[i] = fac[i - 1] * i;
		rev[n] = 1 / fac[n];
		for(int i = n; i >= 1; i--)
			rev[i - 1] = rev[i] * i;
	}

	MI get(int n, int k) {
		return fac[n] * rev[n - k] * rev[k];
	}
};
