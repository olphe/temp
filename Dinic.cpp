class Edge {
public:
	long long int to;
	long long int max_flow;
	long long int rev;
};

class Dinic {
	int V;
public:
	vector<vector<Edge>>edge;
	vector<int>depth;
	vector<int>index;
	Dinic(int n) {
		n++;
		V = n;
		edge.resize(V);
		depth.resize(V);
		index.resize(V);
		return;
	}
	void Add_Edge(int l, int r, int max_flow) {
		edge[l].push_back({ r,max_flow,(int)edge[r].size() });
		edge[r].push_back({ l,max_flow,(int)edge[l].size() - 1 });
		return;
	}
	void Check_Depth(int s) {
		for (int i = 0; i < V; i++) {
			depth[i] = INT_MAX;
		}
		depth[s] = 0;
		queue<int>Q;
		Q.push(s);
		while (!Q.empty()) {
			int cn = Q.front();
			Q.pop();
			for (auto i : edge[cn]) {
				if (i.max_flow > 0 && depth[i.to] == INT_MAX) {
					depth[i.to] = depth[cn] + 1;
					Q.push(i.to);
				}
			}
		}
		return;
	}
	long long int max_flow(int v, int g, long long int ret) {
		if (v == g) {
			return ret;
		}
		for (int i = index[v]; i < edge[v].size(); i++) {
			if (edge[v][i].max_flow > 0 && depth[v] < depth[edge[v][i].to]) {
				long long int d = max_flow(edge[v][i].to, g, min(ret, edge[v][i].max_flow));
				if (d > 0) {
					edge[v][i].max_flow -= d;
					edge[edge[v][i].to][edge[v][i].rev].max_flow += d;
					return d;
				}
			}
		}
		return 0;
	}
	long long Solve(int s, int g) {
		long long int ret = 0;
		while (1) {
			Check_Depth(s);
			if (depth[g] == INT_MAX) {
				return ret;
			}
			for (int i = 0; i < V; i++) {
				index[i] = 0;
			}
			long long int add = 0;
			while ((add = max_flow(s, g, INT_MAX)) > 0) {
				ret += add;
			}
		}
		return ret;
	}
};