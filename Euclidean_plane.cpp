struct  Point {
	long double x;
	long double y;
	Point(long double xx, long double yy) {
		x = xx, y = yy;
	}
	Point() {
	}
	Point operator + (const Point& c)const {
		Point box;
		box.x = x + c.x;
		box.y = y + c.y;
		return box;
	}
	Point operator - (const Point& c)const {
		Point box;
		box.x = x - c.x;
		box.y = y - c.y;
		return box;
	}
	Point operator * (const long double& b)const {
		Point box;
		box.x = x * b;
		box.y = y * b;
		return box;
	}
};

struct Line {
	long double a, b, c;
	Line(const int aa, const int bb, const int cc) {
		a = aa, b = bb, c = cc;
	}
	Line(const Point s, const Point t) {
		if (abs(s.x - t.x) < EPS) {
			a = 1;
			b = 0;
		}
		else {
			b = 1;
			a = (t.y - s.y) / (s.x - t.x);
		}
		c = s.x*a + s.y*b;
	}
};

long double dot(Point a, Point b) {
	return a.x*b.x + a.y*b.y;
}

long double cross(Point a, Point b) {
	return a.x*b.y - b.x*a.y;
}

long double Distance(Point a, Point b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

long double Distance(Point a, pair<Point, Point>b) {
	Line l = Line(b.first, b.second);
	if (abs(l.a*a.x + l.b*a.y - l.c) < EPS) {
		return min(Distance(a, b.first), Distance(a, b.second));
	}
	long double A = pow((b.first.x - b.second.x), 2) + pow((b.first.y - b.second.y), 2);
	long double B = 2 * (a.x - b.first.x)*(b.first.x - b.second.x) + 2 * (a.y - b.first.y)*(b.first.y - b.second.y);
	long double r = B / 2 / A;
	r = -r;
	if (r >= 0 && r <= 1) {
		return Distance(a, Point(b.first.x + r * (b.second.x - b.first.x), b.first.y + r * (b.second.y - b.first.y)));
	}
	else {
		return min(Distance(a, b.first), Distance(a, b.second));
	}
}

bool LineCross(Point a1, Point a2, Point b1, Point b2) {
	return cross(a2 - a1, b1 - a1)*cross(a2 - a1, b2 - a1) < EPS&&cross(b2 - b1, a1 - b1)*cross(b2 - b1, a2 - b1) < EPS && !(abs((a1 - a2).x*(a1 - b1).y - (a1 - a2).y*(a1 - b1).x)<EPS && abs((a1 - a2).x*(a1 - b2).y - (a1 - a2).y*(a1 - b2).x)<EPS&&abs(Distance(a1, a2) - Distance(a1, b1) - Distance(a2, b1)) > EPS&&abs(Distance(a1, a2) - Distance(a2, b2) - Distance(a1, b2)) > EPS&&abs(Distance(b1, b2) - Distance(a1, b1) - Distance(a1, b2)) > EPS&&abs(Distance(b1, b2) - Distance(a2, b1) - Distance(a2, b2)) > EPS);
}

long double Distance(pair<Point, Point>a, pair<Point, Point>b) {
	if (LineCross(a.first, a.second, b.first, b.second))return 0;
	return min({ Distance(a.first,b),Distance(a.second,b),Distance(b.first,a),Distance(b.second,a) });
}

Point LineCross(Line a, Line b) {
	Point ret;
	ret.x = (a.c*b.b - a.b*b.c) / (a.a*b.b - a.b*b.a);
	ret.y = -(a.c*b.a - a.a*b.c) / (a.a*b.b - a.b*b.a);
	return ret;
}

long double TriangleArea(Point a, Point b, Point c) {
	long double A, B, C;
	A = Distance(a, b);
	B = Distance(a, c);
	C = Distance(b, c);
	long double S = (A + B + C) / 2;
	return sqrt(S*(S - A)*(S - B)*(S - C));
}

bool IsPointLeft(pair<Point, Point>a, Point b) {
	a.second = a.second - a.first;
	b = b - a.first;
	a.first = a.first - a.first;
	long double radline = atan2(a.second.y, a.second.x);
	long double radpoint = atan2(b.y, b.x) - radline;
	if (sin(radpoint) >= -EPS)return true;
	else return false;
}

bool IsPointInPolygon(Point p, vector<Point>poly) {
	bool ret = true;
	for (int i = 0; i < poly.size(); i++) {
		if (Distance(p, { poly[i],poly[(i + 1) % poly.size()] }) <= EPS) return true;
		ret &= IsPointLeft({ poly[i],poly[(i + 1) % poly.size()] }, p);
	}
	return ret;
}

long double Area(vector<Point>p) {
	long double ret = 0;
	for (int i = 2; i < p.size(); i++) {
		ret += TriangleArea(p[0], p[i - 1], p[i]);
	}
	return ret;
}

vector<vector<Point>>DividePolygonByLine(vector<Point>p, pair<Point, Point>l) {
	vector<int>cr;
	vector<Point>cp;
	for (int k = 0; k < p.size(); k++) {
		int nx = k + 1;
		nx %= p.size();
		if (LineCross(p[k], p[(k + 1) % p.size()], l.first, l.second)) {
			auto np = LineCross(Line(p[k], p[(k + 1) % p.size()]), Line(l.first, l.second));
			bool flag = true;
			for (auto l : cp) {
				if (Distance(l, np) <= EPS)flag = false;
			}
			if (flag) {
				cr.push_back(k);
				cp.push_back(np);
			}
		}
	}
	vector<Point>w;
	vector<Point>x;
	if (cr.size() != 2)return vector<vector<Point>>(1, p);
	int cnt = cr[0];
	do {
		if (w.empty() || Distance(w.back(), p[cnt]) > EPS)w.push_back(p[cnt]);
		if (cnt == cr[0]) {
			if (w.empty() || Distance(w.back(), cp[0]) > EPS)w.push_back(cp[0]);
			if (w.empty() || Distance(w.back(), cp[1]) > EPS)w.push_back(cp[1]);
			cnt = cr[1] + 1;
			cnt %= p.size();
		}
		else if (cnt == cr[1]) {
			if (w.empty() || Distance(w.back(), cp[1]) > EPS)w.push_back(cp[1]);
			if (w.empty() || Distance(w.back(), cp[0]) > EPS)w.push_back(cp[0]);
			cnt = cr[0] + 1;
			cnt %= p.size();
		}
		else {
			cnt++;
			cnt %= p.size();
		}
	} while (cnt != cr[0]);
	cnt = cr[1];
	do {
		if (x.empty() || Distance(x.back(), p[cnt]) > EPS)x.push_back(p[cnt]);
		if (cnt == cr[0]) {
			if (x.empty() || Distance(x.back(), cp[0]) > EPS)x.push_back(cp[0]);
			if (x.empty() || Distance(x.back(), cp[1]) > EPS)x.push_back(cp[1]);
			cnt = cr[1] + 1;
			cnt %= p.size();
		}
		else if (cnt == cr[1]) {
			if (x.empty() || Distance(x.back(), cp[1]) > EPS)x.push_back(cp[1]);
			if (x.empty() || Distance(x.back(), cp[0]) > EPS)x.push_back(cp[0]);
			cnt = cr[0] + 1;
			cnt %= p.size();
		}
		else {
			cnt++;
			cnt %= p.size();
		}
	} while (cnt != cr[1]);
	vector<vector<Point>>ret;
	ret.push_back(w);
	ret.push_back(x);
	return ret;
}

struct Circle {
	long double x, y, r;
	void Input() {
		cin >> x >> y >> r;
	}
	bool operator==(const Circle&c)const {
		return x == c.x&&y == c.y&&r == c.r;
	}
};

vector<Point>CircleCross(Circle a, Circle b) {
	vector<Point>ret;
	Point ap(a.x, a.y);
	Point bp(b.x, b.y);
	Point dp = bp - ap;
	auto dis = Distance(ap, bp);
	if (a == b)return ret;
	if (a.r + b.r < Distance(ap, bp))return ret;
	if (abs(a.r + b.r - dis) <= EPS) {
		ret.push_back(ap + dp * (a.r / (a.r + b.r)));
		return ret;
	}
	if (abs(abs(a.r - b.r) - dis) <= EPS) {
		ret.push_back(ap + dp * (a.r / (a.r - b.r)));
	}
	long double ad;
	ad = (a.r*a.r - b.r*b.r + dis * dis) / 2 / dis;
	Point cp = ap + dp * (ad / dis);
	long double amari = sqrt(a.r*a.r - ad * ad);
	ret.push_back(cp + Point(-dp.y, dp.x)*(amari / dis));
	ret.push_back(cp - Point(-dp.y, dp.x)*(amari / dis));
	return ret;
}

vector<pair<Point, Point>>Common_Tangent(Circle a, Circle b, long double inf) {
	long double pi = acos(-1);
	Point ap = Point(a.x, a.y);
	Point bp = Point(b.x, b.y);
	Point dp = bp - ap;
	vector<pair<Point, Point>>ret;
	long double rad = atan2(dp.y, dp.x);
	long double d = hypot(dp.y, dp.x);
	if (a.r + b.r <= d) {
		long double newrad = asin((a.r + b.r) / d);
		{
			long double fd = hypot(inf, a.r);
			long double lrad = atan2(a.r, -inf);
			long double rrad = atan2(a.r, inf);
			pair<Point, Point>l = { Point(fd*cos(lrad + rad - newrad),fd*sin(lrad + rad - newrad)),Point(fd*cos(rrad + rad - newrad),fd*sin(rrad + rad - newrad)) };
			ret.push_back({ l.first + ap,l.second + ap });
		}
		newrad *= -1;
		{
			long double fd = hypot(inf, -a.r);
			long double lrad = atan2(-a.r, -inf);
			long double rrad = atan2(-a.r, inf);
			pair<Point, Point>l = { Point(fd*cos(lrad + rad - newrad),fd*sin(lrad + rad - newrad)),Point(fd*cos(rrad + rad - newrad),fd*sin(rrad + rad - newrad)) };
			ret.push_back({ l.first + ap,l.second + ap });
		}
	}
	if (abs(a.r - b.r) <= d) {
		long double newrad = asin(abs(a.r - b.r) / d);
		{
			long double fd = hypot(inf, a.r);
			long double lrad = atan2(a.r, -inf);
			long double rrad = atan2(a.r, inf);
			pair<Point, Point>l = { Point(fd*cos(lrad + rad - newrad),fd*sin(lrad + rad - newrad)),Point(fd*cos(rrad + rad - newrad),fd*sin(rrad + rad - newrad)) };
			ret.push_back({ l.first + ap,l.second + ap });
		}
		newrad *= -1;
		{
			long double fd = hypot(inf, -a.r);
			long double lrad = atan2(-a.r, -inf);
			long double rrad = atan2(-a.r, inf);
			pair<Point, Point>l = { Point(fd*cos(lrad + rad - newrad),fd*sin(lrad + rad - newrad)),Point(fd*cos(rrad + rad - newrad),fd*sin(rrad + rad - newrad)) };
			ret.push_back({ l.first + ap,l.second + ap });
		}
	}
	return ret;
}