class Graph {

    int V;
    Adjacency* adj;

public:
    Graph(int V){
        this->V = V;
        adj = new Adjacency[V];
    }
    void addEdge(int v, int w){
        adj[v].push(w);
    }
    
    //Heling functions
    void dfs(int u, bool visited[], list<int>& Stack) {
        visited[u] = true;
        for(int i = 0; i < adj[u].getSize(); ++i) {
            int adjacent = adj[u].getElement(i);
            if(!visited[adjacent]) {
                dfs(adjacent, visited, Stack);
                
            }
        }
        Stack.push_back(u);
    }
    void topologicalSort(){
        //TODO
        bool* visited = new bool[V];
        list<int> Stack;
        for(int i = 0; i < V; ++i) {
            visited[i] = false;
        }
        for(int i = 0; i < V; ++i) {
            if(visited[i] == false) dfs(i, visited, Stack);
        }
        while(!Stack.empty()) {
            cout << Stack.back() << " ";
            Stack.pop_back();
        }
        delete[] visited;
    }
};
