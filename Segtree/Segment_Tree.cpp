class Segment_Tree {
	vector<long long int>v;
	int num;
	long long int ret;
	bool is_min;
	long long int Update(int place) {
		if (place >= v.size() / 2) {
			return v[place];
		}
		if (is_min) {
			v[place] = min(Update(place * 2), Update(place * 2 + 1));
			return v[place];
		}
		v[place] = max(Update(place * 2), Update(place * 2 + 1));
		return v[place];
	}
public:
	Segment_Tree(int n, bool min) {
		n++;
		num = 1;
		while (num < n * 2) {
			num *= 2;
		}
		is_min = min;
		if (min) {
			v.resize(num, MOD*MOD);
		}
		else v.resize(num, -MOD*MOD);
	}
	void Insert(int place, long long int num, bool update) {
		place += v.size() / 2;
		v[place] = num;
		if (!update)return;
		place /= 2;
		while (place) {
			if (is_min)v[place] = min(v[place * 2], v[place * 2 + 1]);
			else v[place] = max(v[place * 2], v[place * 2 + 1]);
			place /= 2;
		}
	}
	void TopDown() {
		Update(1);
	}
	long long int RMQ(int a, int b) {
		if (is_min)ret = LLONG_MAX;
		else ret = LLONG_MIN;
		if (is_min) {
			b++;
			for (a += num / 2, b += num / 2; a < b; a >>= 1, b >>= 1) {
				if (a & 1)ret = min(ret, v[a++]);
				if (b & 1)ret = min(ret, v[--b]);
			}
		}
		else {
			b++;
			for (a += num / 2, b += num / 2; a < b; a >>= 1, b >>= 1) {
				if (a & 1)ret = max(ret, v[a++]);
				if (b & 1)ret = max(ret, v[--b]);
			}
		}
		return ret;
	}
};