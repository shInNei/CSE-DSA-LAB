void dfs(int u, vector<vector<int>>& friends, vector<bool>& visited) {
    visited[u] = true;
    
    for(int i = 0; i < int(friends[u].size()); ++i) {
        int adjacent = friends[u][i];
        if (!visited[adjacent]) {
            dfs(adjacent, friends, visited);
        }
    }
}
int numberOfFriendGroups(vector<vector<int>>& friends) {
    // STUDENT ANSWER
    vector<bool> visited(friends.size(), false);
    int count = 0;
    for(int i = 0; i < int(friends.size()); ++i) {
         if (!visited[i]) {
            dfs(i, friends, visited);
            ++count;
        }
    }
    return count;
}
