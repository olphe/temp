struct Edge {
	int to;
	long long int capa;
	long long int cost;
	unsigned long long int rev_index;
};

class Min_Cost_Flow {
	int n;
	bool d;
	vector<vector<Edge>>edge;
	vector<long long int>potent;
	vector<long long int>dist;
	vector<int>pre_node;
	vector<int>pre_edge;
public:
	Min_Cost_Flow(int node, bool directed) {
		node += 2;
		n = node;
		if (directed)d = true;
		else d = false;
		edge.resize(n);
		potent.resize(n);
		dist.resize(n);
		pre_node.resize(n);
		pre_edge.resize(n);
		return;
	}
	void Add_Edge(int s, int g, long long int cap, long long int cost) {
		if (!d) {
			edge[s].push_back({ g,cap,cost,edge[g].size() });
			edge[g].push_back({ s,0,-cost ,edge[s].size() - 1 });
		}
		else {////Fix!Fix!Fix!!!!!!!
			edge[s].push_back({ g,cap,cost,edge[g].size() });
			edge[g].push_back({ s,cap,cost ,edge[s].size() - 1 });
		}
	}
	long long int Solve(int s, int g, long long int f) {
		long long int ret = 0;
		for (auto &i : potent)i = 0;
		while (f > 0) {
			priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<pair<long long int, int>>>PQ;
			for (auto &i : dist)i = MOD * MOD;
			dist[s] = 0;
			PQ.push({ dist[s],s });
			while (!PQ.empty()) {
				long long int c = PQ.top().first;
				int cn = PQ.top().second;
				PQ.pop();
				if (dist[cn] < c)continue;
				int cnt = 0;
				for (auto &i : edge[cn]) {
					if (i.capa > 0 && dist[i.to] > dist[cn] + i.cost + potent[cn] - potent[i.to]) {
						dist[i.to] = dist[cn] + i.cost + potent[cn] - potent[i.to];
						pre_node[i.to] = cn;
						pre_edge[i.to] = cnt;
						PQ.push({ dist[i.to],i.to });
					}
					cnt++;
				}
			}
			if (dist[g] == MOD * MOD)return -1;
			for (int i = 0; i < n; i++) potent[i] += dist[i];
			long long int d = f;
			for (int i = g; i != s; i = pre_node[i]) {
				d = min(d, edge[pre_node[i]][pre_edge[i]].capa);
			}
			f -= d;
			ret += d * potent[g];
			for (int i = g; i != s; i = pre_node[i]) {
				auto &e = edge[pre_node[i]][pre_edge[i]];
				e.capa -= d;
				edge[i][e.rev_index].capa += d;
			}
		}
		return ret;
	}
};
