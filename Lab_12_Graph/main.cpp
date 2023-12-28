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
	void DFSHelp(int v, bool visited[], Adjacency* traversedList) {
	   visited[v] = true;
	   traversedList->push(v);
	   for(int i = 0; i < adj[v].getSize(); ++i) {
	       int adjacent = adj[v].getElement(i);
	       if(!visited[adjacent]) {
	           DFSHelp(adjacent, visited, traversedList);
	       }
	   }
	}
	Adjacency *DFS(int v)
    {
        // v is a vertex we start DFS
        bool visited[V] = {false};
        Adjacency* traversedList = new Adjacency;
        DFSHelp(v, visited, traversedList);
        return traversedList;
	}
};