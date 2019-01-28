class Lowest_Common_Ancestor {
	vector<int>depth;
	vector<vector<int>>parent;
	vector<vector<int>>edge;
	int height = 0;
	int node;
public:
	Lowest_Common_Ancestor(int num) {
		num++;
		node = num;
		while (num) {
			height++;
			num /= 2;
		}
		parent.resize(height);
		edge.resize(node);
		depth.resize(node);
		for (int i = 0; i < height; i++)parent[i].resize(node);
	}
	void Add_Edge(int a, int b) {
		edge[a].push_back(b);
		edge[b].push_back(a);
		return;
	}
	void Update(int rtnode) {
		queue<int>QQ;
		depth[rtnode] = 0;
		for (int i = 1; i < node; i++) depth[i] = INT_MAX;
		QQ.push(rtnode);
		while (!QQ.empty()) {
			int c = QQ.front();
			for (auto i : edge[c]) {
				if (depth[i] > depth[c] + 1) {
					depth[i] = depth[c] + 1;
					QQ.push(i);
				}
			}
			QQ.pop();
		}
		parent[0][rtnode] = -1;
		for (int i = 1; i < node; i++) {
			for (auto j : edge[i]) {
				if (depth[i] - 1 == depth[j]) {
					parent[0][i] = j;
					break;
				}
			}
		}
		for (int i = 0; i < height - 1; i++) {
			for (int j = 0; j < node; j++) {
				if (parent[i][j] < 0)parent[i + 1][j] = -1;
				else parent[i + 1][j] = parent[i][parent[i][j]];
			}
		}
		return;
	}
	int LCA(int u, int v) {
		if (depth[u] > depth[v])swap(u, v);
		for (int i = 0; i < height; i++) {
			if ((depth[v] - depth[u]) >> i & 1) {
				v = parent[i][v];
			}
		}
		if (u == v)return u;
		for (int i = height - 1; i >= 0; i--) {
			if (parent[i][v] != parent[i][u]) {
				u = parent[i][u];
				v = parent[i][v];
			}
		}
		return parent[0][u];
	}
	int Dist(int u, int v) {
		return depth[u] + depth[v] - depth[LCA(u, v)] * 2;
	}
};