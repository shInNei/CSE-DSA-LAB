void dfs(int e, vector<vector<int>>& edges, vector<bool>& visited) {
    visited[e] = true;
    for(int i = 0; i < int(edges[e].size()); ++i) {
        int adjacent = edges[e][i];
        if(!visited[adjacent]) dfs(adjacent, edges, visited);
    }
}
int connectedComponents(vector<vector<int>>& edges) {
    // STUDENT ANSWER
    vector<bool> visited(edges.size(), false);
    int ComponentCount = 0;
    for(int i = 0; i < int(edges.size()); ++i) {
        if(visited[i] == false) {
            dfs(i, edges, visited);
            ++ComponentCount;   
        }
    }
    return ComponentCount;
}
