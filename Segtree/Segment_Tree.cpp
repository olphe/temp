template <typename Monoid> class SegmentTree {
	int sz;
	vector<Monoid>v;
	using F = function < Monoid(Monoid, Monoid) >;
	F f;
	Monoid id;
public:
	SegmentTree(int n, F _f, Monoid _id) :f(_f), id(_id) {
		sz = 1;
		while (sz < n) {
			sz <<= 1;
		}
		v.assign(sz * 2, id);
	}
	void Set(int p, Monoid x) {
		p += sz;
		v[p] = x;
	}
	void Build() {
		for (int i = sz - 1;i > 0;i--) {
			v[i] = f(v[i * 2], v[i * 2 + 1]);
		}
	}
	void Update(int p, Monoid x) {
		p += sz;
		v[p] = x;
		p >>= 1;
		while (p) {
			v[p] = f(v[p * 2], v[p * 2 + 1]);
			p >>= 1;
		}
	}
	Monoid Query(int a, int b) { //[)
		Monoid Lret = id;
		Monoid Rret = id;
		a += sz;
		b += sz;
		while (a < b) {
			if (a & 1) Lret = f(Lret, v[a++]);
			if (b & 1)Rret = f(v[--b], Rret);
			a >>= 1;
			b >>= 1;
		}
		return f(Lret, Rret);
	}
	Monoid operator[](int p) const
	{
		return v[p + sz];
	}
};