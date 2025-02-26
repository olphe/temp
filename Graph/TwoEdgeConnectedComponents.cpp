const int inf = 1e9;

class TwoEdgeConnectedComponents {
	int num;
	vector<vector<int>>edge;
	vector<int>parent;
	vector<int>dis;
	vector<int>imos;
	int root;
	vector<int>used;
	void FirstDFS(int node, int p = -1) {
		for (auto i : edge[node]) {
			if (i == p) {
				p = -1;
				continue;
			}
			if (dis[i] == inf) {
				parent[i] = node;
				dis[i] = dis[node] + 1;
				FirstDFS(i, node);
			}
			if (dis[i] <= dis[node] - 1) {
				imos[node]++;
				imos[i]--;
			}
		}
		if (parent[node] >= 0)imos[parent[node]] += imos[node];
	}
	void SecondDFS(int node) {
		if (parent[node] == -1)comp[node] = node;
		else {
			if (imos[node])comp[node] = comp[parent[node]];
			else comp[node] = node;
		}
		for (auto i : edge[node]) {
			if (parent[i] == node&&!used[i]) {
				used[i] = 1;
				SecondDFS(i);
			}
		}
	}
public:
	vector<int>comp;
	TwoEdgeConnectedComponents(int n) {
		num = n;
		edge.resize(num);
		parent.resize(num);
		dis.resize(num);
		imos.resize(num);
		used.resize(num);
		comp.resize(num, -1);
		root = 0;
	}
	void Add_Edge(int a, int b) {
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	void Build(int r) {
		root = r;
		for (auto& i : dis)i = inf;
		dis[root] = 0;
		parent[root] = -1;
		FirstDFS(root);
		SecondDFS(root);
	}
	void DEBUG() {
		for (int i = 0; i < num; i++) {
			cout << i << " " << comp[i] << endl;
		}
	}
};