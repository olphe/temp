
class EulerTour {	//	0-indexed
public:
	vector<int>tour;
	vector<int>depth;
	vector<int>l;
	vector<int>r;
private:
	int node;
	vector<vector<int>>edge;
	int root = 0;
	void DFS(int n) {
		for (auto i : edge[n]) {
			if (depth[n] < depth[i]) {
				tour.push_back(n);
				DFS(i);
			}
		}
		tour.push_back(n);
		return;
	}
	void BFS() {
		for (auto &i : depth)i = MOD;
		depth[root] = 0;
		queue<int>Q;
		Q.push(root);
		while (!Q.empty()) {
			int cn = Q.front();
			int c = depth[cn];
			Q.pop();
			for (auto i : edge[cn]) {
				if (depth[i] > c + 1) {
					depth[i] = c + 1;
					Q.push(i);
				}
			}
		}
		return;
	}
public:
	EulerTour(int n, int ro) {
		node = n;
		node++;
		root = ro;
		edge.resize(node);
		depth.resize(node, MOD);
		l.resize(node, MOD);
		r.resize(node, 0);
		return;
	}
	void Add_Edge(int a, int b) {
		edge[a].push_back(b);
		edge[b].push_back(a);
		return;
	}
	void Retour() {
		if (!tour.empty())tour.clear();
		BFS();
		DFS(root);
		for (int i = 0; i < tour.size(); i++) {
			l[tour[i]] = min(l[tour[i]], i);
			r[tour[i]] = min(r[tour[i]], i);
		}
		return;
	}
};