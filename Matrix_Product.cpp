vector<vector<long long int>>matrix_product(vector<vector<long long int>>v, vector<vector<long long int>>w) {
	vector<vector<long long int>>ret(v.size(), vector<long long int>(w.front().size()));
	for (int i = 0; i < ret.size(); i++) {
		for (int j = 0; j < ret[i].size(); j++) {
			for (int k = 0; k < w.size(); k++) {
				ret[i][j] += v[i][k] * w[k][j];
			}
		}
	}
	return ret;
}