template <typename T>
class ConvexHullTrick {//use long double
	T xmin, xmax;
	bool is_min;
	set<pair<pair<T, T>, pair<T, T>>>st_a;
	set<pair<pair<T, T>, pair<T, T>>>st_l;
public:
	ConvexHullTrick(const T lft, const T rht, const bool m) {//xmin xmax get max or min
		xmin = lft, xmax = rht;
		is_min = m;
	}
	pair<T, T> GetLine(T x) {
		auto it = st_l.lower_bound({ { x,x },{ (T)xmin,(T)xmin } });
		it = prev(it);
		if (is_min) {
			return make_pair(-it->second.first, -it->second.second);
		}
		return it->second;
	}
	T GetValue(T x) {
		auto it = st_l.lower_bound({ { x,x },{ (T)xmin,(T)xmin } });
		it = prev(it);
		if (is_min) {
			return it->second.first*x*(-1) - it->second.second;
		}
		return it->second.first*x + it->second.second;
	}
	void InsertLine(T a, T b) {
		if (is_min) {
			a *= -1, b *= -1;
		}
		auto in = make_pair(make_pair(a, b), make_pair((T)xmin, (T)xmin));
		auto it = st_a.lower_bound(in);
		if (it != st_a.end()) {//maue ni hen ga areba owari
			if (it->first.first == a && it->first.second>b)return;
		}
		while (it != st_a.end()) {
			T c, d;
			c = it->first.first;
			d = it->first.second;
			T cross = (d - b) / (a - c);
			if (cross <= it->second.first)break;
			else if (cross<it->second.second) {
				in.second.second = cross;
				auto nx = *it;
				nx.second.first = cross;
				st_l.erase(make_pair(it->second, it->first));
				st_a.erase(it);
				st_a.insert(nx);
				st_l.insert(make_pair(nx.second, nx.first));
				it = st_a.lower_bound(in);
				break;
			}
			else {
				in.second.second = cross;
				st_l.erase(make_pair(it->second, it->first));
				it = st_a.erase(it);
			}
		}
		if (it == st_a.end()) {
			in.second.second = xmax;
			in.second.first = xmax;
		}
		it = st_a.lower_bound(in);
		while (it != st_a.begin()) {
			it = prev(it);
			if (a == it->first.first) {
				st_l.erase(make_pair(it->second, it->first));
				it = st_a.erase(it);
				continue;
			}
			T c, d;
			c = it->first.first;
			d = it->first.second;
			T cross = (d - b) / (a - c);
			if (cross >= it->second.second) {
				it = st_a.lower_bound(in);
				break;
			}
			else if (cross>it->second.first) {
				in.second.first = cross;
				auto nx = *it;
				nx.second.second = cross;
				st_l.erase(make_pair(it->second, it->first));
				it = st_a.erase(it);
				st_a.insert(nx);
				st_l.insert(make_pair(nx.second, nx.first));
				break;
			}
			else {
				in.second.first = cross;
				st_l.erase(make_pair(it->second, it->first));
				it = st_a.erase(it);
			}
		}
		if (it == st_a.begin()) {
			in.second.first = xmin;
		}
		in.second.first = max(in.second.first, xmin);
		in.second.second = min(in.second.second, xmax);
		if (in.second.first<in.second.second) {
			st_a.insert(in);
			st_l.insert(make_pair(in.second, in.first));
		}
	}
	void DEBUG() {
		for (auto i : st_a) {
			cout << setprecision(15) << i.first.first << " " << i.first.second << "   " << i.second.first << " " << i.second.second << endl;
		}
		cout << "//////" << endl;
		for (auto i : st_l) {
			cout << setprecision(15) << i.first.first << " " << i.first.second << "   " << i.second.first << " " << i.second.second << endl;
		}
	}
};