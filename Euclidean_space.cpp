
struct Point3d {
	long double x, y, z;
	Point3d(const long double xx = 0, const long double yy = 0, const long double zz = 0) {
		x = xx, y = yy, z = zz;
	}
	void Input() {
		cin >> x >> y >> z;
	}
	long double Distance(Point3d p) {
		return hypot(hypot(x - p.x, y - p.y), z - p.z);
	}
	Point3d operator+(const Point3d&p)const {
		return Point3d(x + p.x, y + p.y, z + p.z);
	}
	Point3d operator-(const Point3d&p)const {
		return Point3d(x - p.x, y - p.y, z - p.z);
	}
	Point3d operator*(const long double r)const {
		return Point3d(x*r, y*r, z*r);
	}
	void Output() {
		cout << fixed << setprecision(20) << x << " " << y << " " << z << endl;
	}
};

struct Line {
	Point3d st, ed;
	Line(const Point3d aa, const Point3d bb) {
		st = aa, ed = bb;
	}
	long double Distance(Point3d p) {
		p = p - st;
		auto ced = ed - st;
		auto cst = st - st;
		{
			long double rad = atan2(ced.z, ced.x);
			p = Point3d(hypot(p.x, p.z)*cos(atan2(p.z, p.x) - rad), p.y, hypot(p.x, p.z)*sin(atan2(p.z, p.x) - rad));
			ced = Point3d(hypot(ced.x, ced.z), ced.y, 0);
		}
		{
			long double rad = atan2(ced.y, ced.x);
			p = Point3d(hypot(p.x, p.y)*cos(atan2(p.y, p.x) - rad), hypot(p.x, p.y)*sin(atan2(p.y, p.x) - rad), p.z);
			ced = Point3d(hypot(ced.x, ced.y), 0, 0);
		}
		p = Point3d(p.x, hypot(p.y, p.z), 0);
		if (0 <= p.x&&p.x <= ced.x)return p.y;
		return hypot(min(abs(p.x), abs(p.x - ced.x)), p.y);
	}
	bool Intersect(Point3d p, long double r) {
		return Distance(p) <= r;
	}
};

Point3d reflect(Point3d a, Point3d b) {
	long double radz = atan2(b.z, b.x);
	a = Point3d(hypot(a.x, a.z)*cos(atan2(a.z, a.x) - radz), a.y, hypot(a.x, a.z)*sin(atan2(a.z, a.x) - radz));
	b = Point3d(hypot(b.x, b.z), b.y, 0);
	long double rady = atan2(b.y, b.x);
	a = Point3d(hypot(a.x, a.y)*cos(atan2(a.y, a.x) - rady), hypot(a.x, a.y)*sin(atan2(a.y, a.x) - rady), a.z);
	b = Point3d(hypot(b.x, b.y), 0, 0);
	a.x *= -1;
	radz *= -1, rady *= -1;
	a = Point3d(hypot(a.x, a.y)*cos(atan2(a.y, a.x) - rady), hypot(a.x, a.y)*sin(atan2(a.y, a.x) - rady), a.z);
	a = Point3d(hypot(a.x, a.z)*cos(atan2(a.z, a.x) - radz), a.y, hypot(a.x, a.z)*sin(atan2(a.z, a.x) - radz));
	return a;
}