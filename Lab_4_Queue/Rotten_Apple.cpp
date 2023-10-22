#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
// iostream, vector and queue are included
// Hint: use breadth-first-search
#include <tuple>
int secondsToBeRotten(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> visited = grid;
    queue<pair<int,int>> q; // chứa rotten apple
    int FOrange = 0;
    for(int i = 0; i < n; i++) { // Tìm rotten và fresh ban đầu
        for(int j = 0; j < m; j++) {
            if(visited[i][j] == 2) q.push({i,j});
            if(visited[i][j] == 1) FOrange++;
        }
    }
    
    if(FOrange == 0) return 0; // Hư trong 0 giây
    if(q.empty()) return -1; // không có rotten sao rot
    
    int second = -1;
    // 4 hướng 
    vector<pair<int,int>> dir = {{1, 0},{-1, 0},{0, -1},{0, 1}};
    while(!q.empty()) {
        int size = q.size();
        while(size--){
            int x,y;
            std::tie(x,y) = q.front();
            q.pop();
            for(pair<int,int> d : dir) {
                int dx,dy;
                std::tie(dx,dy) = d;
                int i = x + dx;
                int j = y + dy;
                if(i >= 0 && i < n && j >= 0 && j < m && visited[i][j] == 1) {
                    visited[i][j] = 2;
                    FOrange--;
                    q.push({i,j});
                }
            }
        }
        second++;
    }
    if(FOrange == 0) return second;
    else return -1;
}
int main() {
     int rows, cols;
    cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) cin >> grid[i][j];
    }
    cout << secondsToBeRotten(grid);
}