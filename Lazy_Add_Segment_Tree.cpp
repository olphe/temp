class Add_Segment_Tree {
	vector<long long int>v;
	vector<long long int>add;
	vector<long long int>modi;
	vector<int>l;
	vector<int>r;
	int num;
	long long int ret;
	void Left(int place) {
		if (place >= v.size() / 2) {
			l[place] = place - v.size() / 2;
			return;
		}
		Left(place * 2);
		Left(place * 2 + 1);
		l[place] = l[place * 2];
		return;
	}
	void Right(int place) {
		if (place >= v.size() / 2) {
			r[place] = place - v.size() / 2;
			return;
		}
		Right(place * 2);
		Right(place * 2 + 1);
		r[place] = r[place * 2 + 1];
		return;
	}
	long long int Update(int place) {
		if (place >= v.size() / 2) {
			return v[place];
		}
		v[place] = Update(place * 2) + Update(place * 2 + 1);
		return v[place];
	}
	void Modify(int a, int b, long long int num, int place) {
		if (l[place] >= a && r[place] <= b) {
			modi[place] = num * (r[place] - l[place] + 1);
			v[place] = num * (r[place] - l[place] + 1);
			add[place] = 0;
			return;
		}
		if (l[place] > b || r[place] < a)return;
		if (modi[place] != LLONG_MAX) {
			modi[place * 2] = modi[place * 2 + 1] = modi[place] / 2;
			v[place * 2] = v[place * 2 + 1] = modi[place] / 2;
			add[place * 2] = add[place * 2 + 1] = 0;
			modi[place] = LLONG_MAX;
		}
		add[place * 2] += add[place] / 2;
		add[place * 2 + 1] += add[place] / 2;
		add[place] = 0;
		Modify(a, b, num, place * 2);
		Modify(a, b, num, place * 2 + 1);
		v[place] = v[place * 2] + add[place * 2] + v[place * 2 + 1] + add[place * 2 + 1];
		return;
	}
	void Add(int a, int b, long long int num, int place) {
		if (l[place] >= a && r[place] <= b) {
			if (modi[place] != LLONG_MAX) {
				if (place * 2 < v.size()) {
					modi[place * 2] = modi[place * 2 + 1] = modi[place] / 2;
					v[place * 2] = v[place * 2 + 1] = modi[place] / 2;
					add[place * 2] = add[place * 2 + 1] = 0;
				}
				modi[place] = LLONG_MAX;
			}
			add[place] += num * (r[place] - l[place] + 1);
			return;
		}
		if (l[place] > b || r[place] < a)return;
		if (modi[place] != LLONG_MAX) {
			modi[place * 2] = modi[place * 2 + 1] = modi[place] / 2;
			v[place * 2] = v[place * 2 + 1] = modi[place] / 2;
			add[place * 2] = add[place * 2 + 1] = 0;
			modi[place] = LLONG_MAX;
		}
		add[place * 2] += add[place] / 2;
		add[place * 2 + 1] += add[place] / 2;
		add[place] = 0;
		Add(a, b, num, place * 2);
		Add(a, b, num, place * 2 + 1);
		v[place] = v[place * 2] + add[place * 2] + v[place * 2 + 1] + add[place * 2 + 1];
		return;
	}
	void Sum(int a, int b, int place) {
		if (l[place] >= a && r[place] <= b) {
			if (modi[place] != LLONG_MAX) {
				if (place * 2 < v.size()) {
					modi[place * 2] = modi[place * 2 + 1] = modi[place] / 2;
					v[place * 2] = v[place * 2 + 1] = modi[place] / 2;
					add[place * 2] = add[place * 2 + 1] = 0;
				}
				modi[place] = LLONG_MAX;
			}
			ret += v[place] + add[place];
			return;
		}
		if (l[place]>b || r[place]<a) return;
		if (modi[place] != LLONG_MAX) {
			modi[place * 2] = modi[place * 2 + 1] = modi[place] / 2;
			v[place * 2] = v[place * 2 + 1] = modi[place] / 2;
			add[place * 2] = add[place * 2 + 1] = 0;
			modi[place] = LLONG_MAX;
		}
		add[place * 2] += add[place] / 2;
		add[place * 2 + 1] += add[place] / 2;
		add[place] = 0;
		Sum(a, b, place * 2);
		Sum(a, b, place * 2 + 1);
		v[place] = v[place * 2] + add[place * 2] + v[place * 2 + 1] + add[place * 2 + 1];
		return;
	}
public:
	Add_Segment_Tree(int n) {
		n++;
		num = 1;
		while (num < n * 2) {
			num *= 2;
		}
		l.resize(num);
		r.resize(num);
		v.resize(num, 0);
		add.resize(num, 0);
		modi.resize(num, LLONG_MAX);
		Left(1);
		Right(1);
	}
	void Insert(int place, long long int num, bool update) {
		place += v.size() / 2;
		v[place] = num;
		if (!update)return;
		place /= 2;
		while (place) {
			v[place] = v[place * 2] + v[place * 2 + 1];
			place /= 2;
		}
	}
	void Modify(int a, int b, long long int num) {
		Modify(a, b, num, 1);
	}
	void Add(int a, int b, long long int num) {
		Add(a, b, num, 1);
	}
	void Init() {
		Update(1);
	}
	long long int Sum(int a, int b) {
		ret = 0;
		Sum(a, b, 1);
		return ret;
	}
};