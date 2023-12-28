// Some helping functions

int Dijkstra(int** graph, int src, int dst) {
	// TODO: return the length of shortest path from src to dst.
	// khởi tạo tập S khoảng cách vô cực
	int n = 6;
	vector<int> dist(n, INT32_MAX); 
	vector<bool> visited(n, false);
	// Khởi tạo min-heap Q
	// pair<đỉnh 1, đỉnh 2>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	
	// Đưa đỉnh đầu tiên vào min-heap
	pq.push(make_pair(0, src));
	dist[src] = 0;
	
	while(!pq.empty()) {
	    // Lấy phần tử đầu tiên ra
	    int u = pq.top().second;
	    pq.pop();
	    visited[u] = true;
	    
	    for(int v = 0; v < n; ++v) {
	         if (!visited[v] && graph[u][v] && dist[u] != INT32_MAX && dist[u] + graph[u][v] < dist[v]) {
	             dist[v] = dist[u] + graph[u][v];
	             pq.push(make_pair(dist[v], v));
	         }
	    }
	}
	return dist[dst];
}
