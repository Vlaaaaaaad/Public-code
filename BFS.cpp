#include <iostream>
#include <list>
#include <cstdio>

using namespace std;

//-------------------------------------------------------------------------------------------------------------------//

class Graph
{
	int V; // No of nodes
	list<int> *adj; // Adjacency list
public:
	Graph(int V); // Constructor

	void addEdge(int v, int w);
	void BFS(int s); // BFS from node S
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

void Graph::BFS(int s)
{
	// Mark all nodes as not visited
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	// Queue for BFS
	list<int> queue;

	// We mark the current node as visited and we add it to the queue
	visited[s] = true;
	queue.push_back(s);

	// Using list i to store all the neighbor nodes
	list<int>::iterator i;

	while(!queue.empty())
	{
		// Pop the top node and print it
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		// Save all the neighbor nodes. If a neighbor node was not visited, mark it as visited and add it to the queue
		for(i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if(!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
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

	cout << "BFS from node 2: \n";
	g.BFS(2);

	scanf("%*c");
	return 0;
}
