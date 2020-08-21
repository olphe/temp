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

Point LineCross(Line a, Line b) {
	Point ret;
	ret.x = (a.c*b.b - a.b*b.c) / (a.a*b.b - a.b*b.a);
	ret.y = -(a.c*b.a - a.a*b.c) / (a.a*b.b - a.b*b.a);
	return ret;
}

