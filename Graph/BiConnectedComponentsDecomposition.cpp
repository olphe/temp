int inf = 1e9;

class BiConnectedComponentsDecomposition {
	int n;
	const int root_node;
	vector<vector<int>>edge;
	vector<int>ord;
	vector<int>back_ord;
	int temp;
	int root_edge = 0;
	void DFS(int node, int p = -1) {
		back_ord[node] = ord[node] = temp++;
		for (auto i : edge[node]) {
			back_ord[node] = min(back_ord[node], ord[i]);
			if (ord[i] == inf) {
				if (node == root_node) {
					root_edge++;
					if (root_edge == 2) {
						articulation[root_node] = 1;
					}
				}
				DFS(i, node);
				back_ord[node] = min(back_ord[node], back_ord[i]);
				if (node && back_ord[i] >= ord[node]) {
					articulation[node] = 1;
				}
			}
		}
	}
public:
	vector<vector<int>>comp;
	vector<int>articulation;
	BiConnectedComponentsDecomposition(vector<vector<int>>_edge,int _root_node):edge(_edge), root_node(_root_node) {
		temp = root_edge = 0;
		n = edge.size();
		articulation.resize(n);
		ord.resize(n, inf);
		back_ord.resize(n, inf);
	}
	void Build() { // 二重連結成分分解は途中
		temp = 0;
		DFS(root_node);
		vector<int>used(n);
		for (int i = 0;i < n;i++) {
			if (articulation[i] == 0) {
				if (used[i])continue;
				used[i] = 1;
				queue<int>Q;
				Q.push(i);
				vector<int>c;
				while (!Q.empty()) {
					int cn = Q.front();
					c.push_back(cn);
					Q.pop();
					for (auto i : edge[cn]) {
						if (used[i])continue;
						if (articulation[i]) {
							c.push_back(i);
							continue;
						}
						used[i] = 1;
						Q.push(i);
					}
				}
				comp.push_back(c);
			}
			else {
				for (auto j : edge[i]) {
					if (i < j && articulation[j]) {
						comp.push_back({ i,j });
					}
				}
			}
		}
		if (comp.empty()) {
			vector<int>c(n);
			iota(c.begin(), c.end(), 0);
			comp.push_back(c);
		}
	}
	void DEBUG() {
		for (int i = 0;i < n;i++) {
			cout << i << " " << ord[i] << " " << back_ord[i] << " " << articulation[i] << endl;
		}
	}
};