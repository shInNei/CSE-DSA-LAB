#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(vector<vector<int>> graph, int start) {
	int vertices = graph.size();
	bool visited[vertices], first = true;
	for(int i = 0; i < graph.size(); i++) {
	    visited[i] = false;
	}
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while(!q.empty()) {
	    start = q.front();
	    if(first) {
	        cout << start;
	        first = false;
	    }
	    else cout << " " << start;
	    q.pop();
	    for(int i = 0; i < graph[start].size(); i++) {
	        int t = graph[start][i];
	        if(!visited[t]) {
	            visited[t] = true;
	            q.push(t);
	        }
	    }
	}
}

int main() {
    int init_graph[10][10] = {  {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
				    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
				    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
				    {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
				    {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
				    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
	int n = 10;
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (init_graph[i][j]) graph[i].push_back(j);
		}
	}

	bfs(graph, 0);    
}