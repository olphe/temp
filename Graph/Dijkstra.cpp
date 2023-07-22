
struct Edge {
	int to;
	long long int cost;
	Edge(const int t, const int c) {
		to = t, cost = c;
		return;
	}
};

void Dijkstra(vector<vector<Edge>>&edge, vector<long long int>&dis, int root = 0) {
	dis[0] = 0;
	priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<pair<long long int, int>>>PQ;
	PQ.push({ 0,0 });
	while (!PQ.empty()) {
		int cn = PQ.top().second;
		long long int c = PQ.top().first;
		PQ.pop();
		for (auto i : edge[cn]) {
			if (dis[i.to] > c + i.cost) {
				dis[i.to] = c + i.cost;
				PQ.push({ dis[i.to],i.to });
			}
		}
	}
	return;
}