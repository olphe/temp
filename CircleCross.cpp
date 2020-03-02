template<class T>
vector<pair<T, T>>CircleCross(pair<pair<T, T>, T>p, pair<pair<T, T>, T>q) {
	T a, b;
	if (abs(q.first.second - p.first.second) < EPS) {
		a = (p.second*p.second - q.second*q.second + (p.first.first - q.first.first)*(p.first.first - q.first.first)) / 2 / abs((p.first.first - q.first.first));
		vector<pair<T, T>>ret;
		if (a - EPS > p.second)return ret;
		if (a + EPS >= p.second) {
			ret.emplace_back(min(p.first.first, q.first.first) + a, p.first.second);
			return ret;
		}
		b = sqrt(p.second*p.second - a * a);
		ret.emplace_back(min(p.first.first, q.first.first) + a, p.first.second + b);
		ret.emplace_back(min(p.first.first, q.first.first) + a, p.first.second - b);
		return ret;
	}
	a = (p.first.first - q.first.first) / (q.first.second - p.first.second);
	b = (p.second*p.second - q.second*q.second - p.first.first*p.first.first + q.first.first*q.first.first - p.first.second*p.first.second + q.first.second*q.first.second) / 2 / (q.first.second - p.first.second);
	T A, B, C;
	A = 1 + a * a;
	B = -2 * p.first.first + 2 * a*b - 2 * a*p.first.second;
	C = p.first.first*p.first.first + b * b - 2 * b*p.first.second + p.first.second*p.first.second - p.second*p.second;
	vector<pair<T, T>>ret;
	if (B*B - 4 * A*C > 0) {
		T x = (-B + sqrt(B*B - 4 * A*C)) / 2 / A;
		T y = a * x + b;
		ret.emplace_back(x, y);
		x = (-B - sqrt(B*B - 4 * A*C)) / 2 / A;
		y = a * x + b;
		ret.emplace_back(x, y);
	}
	else if (B*B - 4 * A*C >= -EPS) {
		T x = -B / 2 / A;
		T y = a * x + b;
		ret.emplace_back(x, y);
	}
	return ret;
}