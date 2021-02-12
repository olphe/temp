
struct Bridge {
	int num;
	vector<int>ord;
	vector<int>pre;
	vector<vector<pair<int, int>>>edge;
	vector<pair<int, int>>ord_edge;
	vector<int>bridge_idx;
	vector<int>used;
	int idx = 0;
	Bridge(int n) :num(n) {
		ord.resize(n);
		pre.resize(n);
		edge.resize(n);
		used.resize(n);
	}
	void Add_Edge(int a, int b) {
		edge[a].emplace_back(b, idx);
		edge[b].emplace_back(a, idx);
		ord_edge.emplace_back(a, b);
		idx++;
	}
	void DFS(int node, int par = -1) {
		used[node] = 1;
		for (auto[to, idx] : edge[node]) {
			if (to == par)continue;
			if (used[to]) {
				pre[node] = min(pre[node], pre[to]);
			}
			else {
				pre[to] = ord[to] = ord[node] + 1;
				DFS(to, node);
				pre[node] = min(pre[node], pre[to]);
				if (pre[to] == ord[to]) {
					bridge_idx.push_back(idx);
				}
			}
		}
	}
	void Solve() {
		DFS(0);
	}
};