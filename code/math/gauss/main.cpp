// todo: dokończyć kod, poprawić komentarze, includować header

int gauss(vector<vector<double>> a, vector<double> &ans) {
	int n = int(a.size()), m = int(a[0].size()) - 1;
	static constexpr double epsilon = 1e-6;
	vector<int> where(m, -1);

	for(int col = 0, row = 0; col < m && row < n; ++col) {
		// searching for partial pivot element
		int pivot = row;
		for(int i = row + 1; i < n; ++i)
			if(abs(a[i][col]) > abs(a[pivot][col]))
				pivot = i;

		// found any?
		if(abs(a[pivot][col]) < epsilon)
			continue;

		// swapping row with pivot
		for(int i = 0; i <= m; ++i)
			swap(a[row][i], a[pivot][i]);
		where[col] = row;

		// dividing row by first element
		for(int i = col + 1; i <= m; ++i)
			a[row][i] /= a[row][col];
		a[row][col] = 1;

		// substracting row row from other rows
		for(int i = 0; i < n; ++i)
			if(i != row) {
				double c = a[i][col];
				for(int j = 0; j <= m; ++j) 
					a[i][j] -= c * a[row][j];
			}

		++row;
	}

	// todo: return number of solutions (-1, 0, 1)
	return -1;
}
