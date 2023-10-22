#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartite(vector<vector<int>> graph) {
    int n = graph.size();
    vector<int> colour(n);// 0: đ** có màu; 1: màu đỏ; -1: màu xanh
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(colour[i]) continue; // Nào có màu bỏ
        colour[i] = 1; //Tô màu đỉnh i màu đỏ
        // BFS
        // Ban đầu tô 1 đỉnh xong đưa nó vào queue
        for(q.push(i); !q.empty(); q.pop()) { 
           int cur = q.front();
           for(int neighbor : graph[cur]) { // Chạy trong hàng, check những thằng nó nối
                if(!colour[neighbor]) { // Chưa có màu thì tô màu còn lại
                   colour[neighbor] = -colour[cur];
                   q.push(neighbor);
             }
                else if(colour[neighbor] == colour[cur]) return false; // 2 Thằng cạnh nhau cùng màu
        }
     }
    }
    return true;
}

int main() {
    int G[6][6] = { {0, 1, 0, 0, 0, 1},
                {1, 0, 1, 0, 0, 0},
                {0, 1, 0, 1, 0, 0},
                {0, 0, 1, 0, 1, 0},
                {0, 0, 0, 1, 0, 1},
                {1, 0, 0, 0, 1, 0} };
    int n = 6;

    vector<vector<int>> graph(n, vector<int>());
	    for (int i = 0; i < n; ++i) {
		    for (int j = 0; j < n; ++j) {
			    if (G[i][j]) graph[i].push_back(j);
		    }
	    }

    isBipartite(graph) ? cout << "Yes" : cout << "No";    
}