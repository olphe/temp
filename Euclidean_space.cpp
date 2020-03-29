class Coordinate {
public:
	long double x;
	long double y;
	Coordinate operator + (const Coordinate& c)const {
		Coordinate box;
		box.x = x + c.x;
		box.y = y + c.y;
		return box;
	}
	Coordinate operator - (const Coordinate& c)const {
		Coordinate box;
		box.x = x - c.x;
		box.y = y - c.y;
		return box;
	}
};

long double dot(Coordinate a, Coordinate b) {
	return a.x*b.x + a.y*b.y;
}

long double cross(Coordinate a, Coordinate b) {
	return a.x*b.y - b.x*a.y;
}

long double Distance(Coordinate a, Coordinate b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool LineCross(Coordinate a1, Coordinate a2, Coordinate b1, Coordinate b2) {
	return cross(a2 - a1, b1 - a1)*cross(a2 - a1, b2 - a1) < EPS&&cross(b2 - b1, a1 - b1)*cross(b2 - b1, a2 - b1) < EPS && !((a1 - a2).x*(a1 - b1).y == (a1 - a2).y*(a1 - b1).x && (a1 - a2).x*(a1 - b2).y == (a1 - a2).y*(a1 - b2).x&&abs(Distance(a1, a2) - Distance(a1, b1) - Distance(a2, b1)) > EPS&&abs(Distance(a1, a2) - Distance(a2, b2) - Distance(a1, b2)) > EPS&&abs(Distance(b1, b2) - Distance(a1, b1) - Distance(a1, b2)) > EPS&&abs(Distance(b1, b2) - Distance(a2, b1) - Distance(a2, b2)) > EPS);
}