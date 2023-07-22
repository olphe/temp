struct ConvexHullTrick {
	map<long long, pair<long long, long long>>line;
	map<long long, long long>range;
	long long inf;
	ConvexHullTrick(long long inf = 4500000000000000000) :inf(inf) {
		range[-inf] = -21000000000;
		line[-2100000000] = { -inf,-inf };
	}
	long long GetCross(long long a1, long long b1, long long a2, long long b2) {
		if (b1 - b2 >= 0)return (b1 - b2) / (a2 - a1) + 1;
		long long minus = (b2 - b1) / (a2 - a1) + 1;
		return abs((b1 - b2 + (a2 - a1) * minus) / (a2 - a1)) + 1 - minus;
	}
	void AddLine(long long  a, long long  b) {
		if (line.find(a) != line.end()) {
			if (line[a].first >= b)return;
			auto it = line.find(a);
			auto nx = next(it);
			auto pv = prev(it);
			if (nx == line.end()) {
				auto ita = it->first;
				range.erase(it->second.second);
				line.erase(it);
			}
			else {
				auto ita = it->first;
				auto nxa = nx->first;
				auto in = nx->second;
				in.second = GetCross(pv->first, pv->second.first, nx->first, nx->second.first);
				range.erase(it->second.second);
				range.erase(nx->second.second);
				line.erase(ita);
				line.erase(nxa);
				range[in.second] = nxa;
				line[nxa] = in;
			}
		}
		auto nx = line.lower_bound(a);
		auto pv = prev(nx);
		long long lp = GetCross(pv->first, pv->second.first, a, b);
		if (nx != line.end() && a * nx->second.second + b <= nx->first * nx->second.second + nx->second.first) {
			return;
		}
		while (pv->second.second >= lp) {
			range.erase(pv->second.second);
			line.erase(pv);
			nx = line.lower_bound(a);
			pv = prev(nx);
			lp = GetCross(pv->first, pv->second.first, a, b);
		}
		if (nx == line.end()) {
			range[lp] = a;
			line[a] = { b,lp };
		}
		else {
			while (nx != line.end()) {
				auto nnx = next(nx);
				long long rp = GetCross(a, b, nx->first, nx->second.first);
				if (nnx == line.end() || rp < nnx->second.second) break;
				range.erase(nx->second.second);
				line.erase(nx);
				nx = line.lower_bound(a);
			}
			if (nx == line.end()) {
				range[lp] = a;
				line[a] = { b,lp };
			}
			else {
				long long rp = GetCross(a, b, nx->first, nx->second.first);
				if (lp < rp) {
					auto in = nx->second;
					auto nxa = nx->first;
					in.second = rp;
					range.erase(nx->second.second);
					line.erase(nx);
					range[rp] = nxa;
					line[nxa] = in;
					range[lp] = a;
					line[a] = { b,lp };
				}
			}
		}
	}

	long long  GetValue(long long  x) {//getmax
		auto r = prev(range.upper_bound(x));
		long long  ret = r->second * x + line[r->second].first;
		return ret;
	}
	void DEBUG() {
		for (auto i : line) {
			cout << "line " << i.first << " " << i.second.first << " " << i.second.second << endl;
		}
		for (auto i : range) {
			cout << "range " << i.first << " " << i.second << endl;
		}
	}
};