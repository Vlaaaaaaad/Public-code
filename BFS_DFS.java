import java.util.*;
import java.io.*;

public class BFS_DFS
{
	public static void main(String[] args) throws Exception
	{
		int n;
		Graph T;

		T = new Graph();

		Scanner sc = new Scanner(System.in);

		System.out.println("Insert the node you would like the DFS to start from.");

		n = sc.nextInt();
		
		T.DFS(n);

		System.out.println("Insert the node you would like the BFS to start from.");

		n = sc.nextInt();
		
		T.BFS(n);

		sc.close();
	}
}

//--------------------------------------------------------------------------------------------------------------------//

class Graph
{
	int V;
	List<Integer>[] adj;

	Graph() throws Exception
	{
		int i = 0, k = 0, j;

		V = 0;

		String s;
		String[] tokens;

		File graf = new File("Graf.txt");

		FileReader fr = new FileReader(graf);

		LineNumberReader lnr = new LineNumberReader(fr);

		while (lnr.readLine() != null)
		{
			V++;
		}

		fr.close();
		lnr.close();

		adj = new List[V + 1];

		for(int pi = 1; pi <= V; pi++)
			adj[pi] = new ArrayList<Integer>();

		// Knowing how many nodes we have, let's make the adjacency list

		tokens = new String[V];

		Scanner in_file = new Scanner(graf);

		while(in_file.hasNextLine())
		{
			i++;

			s = in_file.nextLine();

			tokens = s.split(" ");

			for(String n: tokens)
			{
				k++;

				j = Integer.parseInt(n);

				adj[i].add(j);
			}
		}

		in_file.close();

		// let's also show a check, just to be sure

		System.out.println("A graph with the following adjacency list has been read and initialized:");
		
		for(int o = 1; o <= V; o++)
			System.out.println(adj[o]);
	}

	//------------------------------------------------------------------------------------------------------------//

	void DFS(int v) throws Exception
	{
		boolean[] visited = new boolean[V + 1];

		for(int i = 1 ; i <= V; i++)
			visited[i] = false;

		PrintWriter pw1 = new PrintWriter("DFS.txt");

		DFSFunction(v, visited, pw1);

		pw1.close();
	}

	//------------------------------------------------------------------------------------------------------------//

	void DFSFunction(int v, boolean[] visited, PrintWriter pw1)
	{
		visited[v] = true;

		pw1.print(v + " ");

		for(Integer n: adj[v])
			if(visited[n] == false)
				DFSFunction(n, visited, pw1);
	}

	//------------------------------------------------------------------------------------------------------------//

	void BFS(int v) throws Exception
	{
		Integer s; 
		PrintWriter pw2 = new PrintWriter("BFS.txt");

		boolean[] visited = new boolean[V + 1];

		LinkedList<Integer> q = new LinkedList<Integer>();

		visited[v] = true;

		q.addFirst(v);

		while(!q.isEmpty())
		{
			s = q.pollLast();

			pw2.print(s + " ");

			for(int n: adj[s])
				if(visited[n] == false)
				{
					visited[n] = true;
					q.addFirst(n);
				}
		}

		pw2.close();
	}
}
