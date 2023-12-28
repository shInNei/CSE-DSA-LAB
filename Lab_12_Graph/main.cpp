class Graph
{
private:
	int V;
	Adjacency *adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new Adjacency[V];
	}
	
	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}
	
    void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
	
	Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        Adjacency* traversedList = new Adjacency;
        bool visited[V];
        for(int i = 0; i < V; ++i) visited[i] = false;
        list<int> queue;
        visited[v] = true;
        queue.push_back(v);
        while(!queue.empty()) {
            v = queue.front();
            traversedList->push(v);
            queue.pop_front();
            for(int i = 0; i < int(adj[v].getSize()); ++i) {
                int adjacent = adj[v].getElement(i);
                if(!visited[adjacent]) {
                    visited[adjacent] = true;
                    queue.push_back(adjacent);
                }
            }
        }
        return traversedList;
	}
};