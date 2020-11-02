class UnionFind {
	vector<int>parent;
	stack<int>child;
	vector<int>sz;
public:
	UnionFind(int num) {
		parent.resize(num);
		sz.resize(num, 1);
		for (int i = 0; i < num; i++) {
			parent[i] = i;
		}
	}
	int Find(int node) {
		if (parent[node] == node)return node;
		else return Find(parent[node]);
	}
	void ReversibleUnite(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u == v)return;
		if (sz[u] < sz[v]) {
			parent[u] = v;
			sz[v] += sz[u];
			child.push(u);
		}
		else {
			sz[u] += sz[v];
			parent[v] = u;
			child.push(v);
		}
	}
	void Undo() {
		int c = child.top();
		child.pop();
		parent[c] = c;
	}
	bool Check_Same(int u, int v) {
		return Find(u) == Find(v);
	}
};