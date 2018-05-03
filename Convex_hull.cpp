const long double EPS = 1e-8;

struct Coordinate {
	long double x;
	long double y;
	bool operator <(const Coordinate& c)const {
		if (y < c.y)return true;
		if (y > c.y)return false;
		if (x < c.x)return true;
		return false;
	}
	bool operator >(const Coordinate& c)const {
		if (y > c.y)return true;
		if (y < c.y)return false;
		if (x > c.x)return true;
		return false;
	}
	Coordinate operator +(const Coordinate& c)const {
		Coordinate box;
		box.x = x + c.x;
		box.y = y + c.y;
		return box;
	}
	Coordinate operator -(const Coordinate& c)const {
		Coordinate box;
		box.x = x - c.x;
		box.y = y - c.y;
		return box;
	}
	long double det(Coordinate a) {
		return x*a.y - y*a.x;
	}
};

struct Convex_hull {
	vector<Coordinate>node;
	vector<Coordinate>ret;
	bool line;
	Convex_hull(bool l) {
		line = l;
	}
	void Add_node(Coordinate n) {
		node.push_back(n);
	}
	vector<Coordinate>solve() {
		sort(node.begin(), node.end());
		int index = 0;
		int num = node.size();
		ret.resize(num * 2);
		for (int i = 0; i < num; i++) {
			if (line) {
				while (index > 1 && (ret[index - 1] - ret[index - 2]).det(node[i] - ret[index - 1]) < -EPS) {
					index--;
				}
			}
			else {
				while (index > 1 && (ret[index - 1] - ret[index - 2]).det(node[i] - ret[index - 1]) < EPS) {
					index--;
				}
			}
			ret[index++] = node[i];
		}
		int box = index;
		for (int i = num - 2; i >= 0; i--) {
			if (line) {
				while (index > box && (ret[index - 1] - ret[index - 2]).det(node[i] - ret[index - 1]) < -EPS) {
					index--;
				}
			}
			else {
				while (index > box && (ret[index - 1] - ret[index - 2]).det(node[i] - ret[index - 1]) < EPS) {
					index--;
				}
			}
			ret[index++] = node[i];
		}
		ret.resize(index - 1);
		return ret;
	}
};