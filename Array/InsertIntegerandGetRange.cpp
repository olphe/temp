class InsertIntegerandGetRange {
	int n;
	vector<int>l, r;
public:
	InsertIntegerandGetRange(int _n) :n(_n) {
		l.resize(n, -1);
		r.resize(n, -1);
	}
	pair<int, int>Insert(int p) {
		if (p < 0 || p >= l.size())exit(-1);
		l[p] = r[p] = p;
		if (p && l[p - 1] != -1) {
			l[p] = l[p - 1];
			r[l[p]] = r[p];
			p = l[p];
		}
		if (r[p] + 1 < n && r[r[p] + 1] != -1) {
			r[p] = r[r[p] + 1];
			l[r[p]] = l[p];
		}
		return { l[p],r[p] };
	}
};