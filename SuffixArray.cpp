class SuffixArray {
	string s;
	vector<int>nx;
	int length = 1;
	int n;
public:
	vector<int>ret;
	vector<int>id;
	vector<int>lcp;
	SuffixArray(string ss) {
		s = ss;
		n = s.size();
		id.resize(n);
		nx.resize(n);
		ret.resize(n);
		lcp.resize(n);
		for (int i = 0; i < n; i++) {
			ret[i] = i;
		}
		for (int i = 0; i < n; i++) {
			id[i] = s[i];
		}
		while (length < n) {
			auto comp = [&](int a, int b) {
				if (id[a] != id[b])return id[a] < id[b];
				int l = -1, r = -1;
				if (a + length < n)l = id[a + length];
				if (b + length < n)r = id[b + length];
				return l < r;
			};
			sort(ret.begin(), ret.end(), comp);
			nx[ret[0]] = 0;
			for (int i = 1; i < n; i++) {
				nx[ret[i]] = nx[ret[i - 1]] + comp(ret[i - 1], ret[i]);
			}
			id = nx;
			length <<= 1;
		}
		for (int i = 0; i < n; i++) {
			int nx = id[i];
			if (nx + 1 == n)continue;
			nx = ret[nx + 1];
			int idx = i;
			if (i&&lcp[id[i - 1]]) {
				lcp[id[i]] = lcp[id[i - 1]] - 1;
				nx += lcp[id[i]];
				idx += lcp[id[i]];
			}
			while (nx < n&&i < n&&s[idx] == s[nx]) {
				lcp[id[i]]++;
				nx++;
				idx++;
			}
		}
	}
};