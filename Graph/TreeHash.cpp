void Random_Vec(vector<long long int>&v, long long int mod) {
	random_device rd;
	mt19937_64 mt(rd());
	for (auto &i : v) {
		i = mt() % mod;
	}
}

pair<long long int, int> Tree_Hash(vector<long long int>&by, vector<vector<int>>&edge, long long int mod, int node, int p = -1) {
	long long int ret = 1;
	int depth = 0;
	vector<long long int>v;
	for (auto i : edge[node]) {
		if (i == p)continue;
		auto box = Tree_Hash(by, edge, mod, i, node);
		v.push_back(box.first);
		depth = max(depth, box.second + 1);
	}
	for (auto i : v) {
		ret *= (by[depth] + i);
		ret %= mod;
	}
	return { ret,depth };
}