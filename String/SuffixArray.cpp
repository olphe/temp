class SuffixArray {
public:
	vector<int>ans;
	vector<int>id;
	vector<int>lcp;
	void InducedSort(vector<int>& ret, const vector<int>& v, const vector<int>& large, vector<int>& lft, vector<int>& rht) {
		for (int i = 0; i < v.size(); i++) {
			if (ret[i] == -1)continue;
			if (ret[i] == 0)continue;
			if (!large[ret[i] - 1])continue;
			ret[lft[v[ret[i] - 1]]++] = ret[i] - 1;
		}
		for (int i = v.size() - 1; i >= 0; i--) {
			if (ret[i] == -1)continue;
			if (ret[i] == 0)continue;
			if (large[ret[i] - 1])continue;
			ret[--rht[v[ret[i] - 1]]] = ret[i] - 1;
		}
	}
	vector<int> Solve(vector<int>v, int mx) {
		vector<int>ret;
		vector<int>large;
		vector<int>num;
		vector<int>nx_lms;
		vector<bool>lms;
		vector<int>rht;
		vector<int>lft;
		if (v.size() == 1) {
			return vector<int>(1);
		}
		large.resize((v.size()));
		nx_lms.resize(v.size(), v.size() - 1);
		lms.resize(v.size());
		lms.back() = true;
		for (int i = v.size() - 2; i >= 0; i--) {
			if (v[i] > v[i + 1]) {
				large[i] = 1;
			}
			else if (v[i] < v[i + 1]) {
				large[i] = 0;
			}
			else {
				large[i] = large[i + 1];
			}
		}
		for (int i = v.size() - 2; i > 0; i--) {
			if (large[i - 1] && !large[i]) {
				lms[i] = true;
				nx_lms[i - 1] = i;
			}
			else {
				nx_lms[i - 1] = nx_lms[i];
			}
		}
		ret.resize(v.size(), -1);
		num.resize(mx + 1);
		lft.resize(mx + 1);
		rht.resize(mx + 1);
		for (auto i : v) {
			num[i]++;
		}
		for (int i = 1; i <= mx; i++) {
			num[i] += num[i - 1];
		}
		rht[0] = num[0];
		for (int i = 1; i <= mx; i++) {
			rht[i] = num[i];
			lft[i] = num[i - 1];
		}
		for (int i = 1; i < v.size(); i++) {
			if (lms[i]) {
				ret[--rht[v[i]]] = i;
			}
		}
		for (int i = 0; i <= mx; i++) {
			rht[i] = num[i];
		}
		InducedSort(ret, v, large, lft, rht);
		vector<int>nxv;
		int nxmx = -1;
		vector<int>conv(v.size());
		vector<int>nxp;
		for (int i = 0; i + 1 < v.size(); i++) {
			if (large[i] && !large[i + 1]) {
				nxp.push_back(i + 1);
			}
		}
		vector<int>bef;
		for (int i = 0; i < v.size(); i++) {
			if (lms[ret[i]]) {
				vector<int> aft;
				for (int j = ret[i]; j <= nx_lms[ret[i]]; j++) {
					aft.push_back(v[j]);
				}
				if (bef != aft) {
					nxmx++;
					bef = aft;
				}
				conv[ret[i]] = nxmx;
			}
		}
		for (int i = 0; i < v.size(); i++) {
			if (lms[i]) {
				nxv.push_back(conv[i]);
			}
		}

		auto nxret = Solve(nxv, nxmx);

		for (auto& i : ret)i = -1;

		rht[0] = num[0];
		lft[0] = 0;
		for (int i = 1; i <= mx; i++) {
			rht[i] = num[i];
			lft[i] = num[i - 1];
		}


		for (int i = nxret.size() - 1; i >= 0; i--) {
			ret[--rht[v[nxp[nxret[i]]]]] = nxp[nxret[i]];
		}

		for (int i = 0; i <= mx; i++) {
			rht[i] = num[i];
		}

		InducedSort(ret, v, large, lft, rht);
		return ret;
	}
	SuffixArray(string s) {
		vector<int>v;
		int mx = 0;
		for (auto i : s) {
			v.push_back(i + 1);
			mx = max(mx, i + 1);
		}
		v.push_back(0);
		ans = Solve(v, mx);
		ans.erase(ans.begin());
		id.resize(ans.size());
		lcp.resize(ans.size());
		for (int i = 0; i < ans.size(); i++) {
			id[ans[i]] = i;
		}
		for (int i = 0; i < id.size(); i++) {
			int nx = id[i];
			if (nx + 1 == id.size())continue;
			nx = ans[nx + 1];
			int idx = i;
			if (i && lcp[id[i - 1]]) {
				lcp[id[i]] = lcp[id[i - 1]] - 1;
				nx += lcp[id[i]];
				idx += lcp[id[i]];
			}
			while (nx < id.size() && i < id.size() && s[idx] == s[nx]) {
				lcp[id[i]]++;
				nx++;
				idx++;
			}
		}
	}
};