#include <iostream>
#include <list>
#include <cstdio>

using namespace std;

//-------------------------------------------------------------------------------------------------------------------//

class Graph
{
	int V; // Number of nodes
	list<int> *adj; // Adjacency list

	void DFSFunction(int v, bool visited[]);
public:
	Graph(int V); // Constructor

	void addEdge(int v, int w);
	void DFS(int v); // DFS from node V
};
 
//-------------------------------------------------------------------------------------------------------------------//

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

//-------------------------------------------------------------------------------------------------------------------//

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

//-------------------------------------------------------------------------------------------------------------------//

void Graph::DFSFunction(int v, bool visited[])
{
	// Mark the current node as visited
	visited[v] = true;
	cout<<v<<" ";

	// Recursive function for all the neighbor nodes of the current node
	list<int>::iterator i;

	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
			DFSFunction(*i, visited);
}

//-------------------------------------------------------------------------------------------------------------------//

void Graph::DFS(int v)
{
	// Mark all nodes as not visited
	bool *visited = new bool[V];

	for(int i = 0; i < V; i++)
		visited[i] = false;

	DFSFunction(v, visited);
}

//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------//

int main()
{
	// Write the graph here
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "DFS from node 2: \n";
	g.DFS(2);

	scanf("%*c");
	return 0;
}
