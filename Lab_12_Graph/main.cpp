#include <iostream>
#include <vector>
#include <list>
using namespace std;

class DirectedGraph 
{ 
	int V;
	vector<list<int>> adj;
public:
	DirectedGraph(int V)
	{
		this->V = V; 
		adj = vector<list<int>>(V, list<int>());
	}
	void addEdge(int v, int w)
	{
		adj[v].push_back(w);
	}
	bool dfs(int u, vector<bool>& visited, vector<bool> recurs) {
	    visited[u] = true;
	    recurs[u] = true;
	    for(list<int>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
	        int adjacent = *it;
	        if (!visited[adjacent]) {
                if (dfs(adjacent, visited, recurs)) {
                    return true;
                }
            } else if (recurs[adjacent]) {
                return true;
            }
	    }
	    recurs[u] = false;
	    return false;
	}
	bool isCyclic()
	{
	    // Student answer
	    vector<bool> visited(V, false);
	    vector<bool> recurs(V, false);
	    for(int i = 0; i < V; ++i) {
	        if(!visited[i] && dfs(i, visited, recurs)) return true;
	    }
	    return false;
	}
}; 