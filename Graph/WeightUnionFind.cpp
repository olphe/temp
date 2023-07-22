class UnionFind {
	vector<int>parent;
	vector<int>rank;
	vector<int>score;
	int ret;
public:
	UnionFind(int num) {
		num++;
		parent.resize(num);
		rank.resize(num);
		score.resize(num);
		for (int i = 0; i < num; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	int Find(int node) {
		ret += score[node];
		if (parent[node] == node)return node;
		else return Find(parent[node]);
	}
	int Score(int node) {
		ret = 0;
		Find(node);
		return ret;
	}
	bool Unite(int u, int v, int c) {
		int ascore = Score(u);
		int bscore = Score(v);
		u = Find(u);
		v = Find(v);
		if (u == v && ascore - c != bscore) {
			return false;
		}
		c += bscore - ascore;
		if (u == v)return true;
		if (rank[u] < rank[v]) {
			parent[u] = v;
			score[u] = c;
		}
		else {
			parent[v] = u;
			score[v] = -c;
			if (rank[u] == rank[v])rank[u]++;
		}
		return true;
	}
	bool Check_Same(int u, int v) {
		return Find(u) == Find(v);
	}
};