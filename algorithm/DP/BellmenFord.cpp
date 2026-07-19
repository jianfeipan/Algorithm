#include "pch.h"


#include <iostream>
#include <limits.h>
#include <vector>


using namespace std;

void BellmanFord(int graph[][3], int V, int E, int from)
{
   // Initialize distance of all vertices as infinite.
   vector<int> distanceTo(V, INT_MAX);

   // initialize distance of source as 0
   distanceTo[from] = 0;

   // Relax all edges |V| - 1 times. A simple
   // shortest path from src to any other
   // vertex can have at-most |V| - 1 edges

   //O(EV)
   for (int i = 0; i < V - 1; i++) 
   {
      for (int j = 0; j < E; j++) {
         if (distanceTo[graph[j][0]] != INT_MAX)
         {
            if (distanceTo[graph[j][0]] + graph[j][2] < distanceTo[graph[j][1]])
            {
               distanceTo[graph[j][1]] = distanceTo[graph[j][0]] + graph[j][2];
            }
         }
      }
   }

   // check for negative-weight cycles.
   // The above step guarantees shortest
   // distances if graph doesn't contain
   // negative weight cycle.  If we get a
   // shorter path, then there is a cycle.
   for (int i = 0; i < E; i++) {
      int x = graph[i][0];
      int y = graph[i][1];
      int weight = graph[i][2];
      if (distanceTo[x] != INT_MAX &&
         distanceTo[x] + weight < distanceTo[y]) // after relex can still relax
         cout << "Graph contains negative"
         " weight cycle"
         << endl;
   }

   cout << "Vertex Distance from Source" << endl;
   for (int i = 0; i < V; i++)
      cout << i << "\t\t" << distanceTo[i] << endl;
}

// Driver program to test above functions
int main()
{

   constexpr int V = 5; // Number of vertices in graph
   int E = 8; // Number of edges in graph

   // Every edge has three values (u, v, w) where
   // the edge is from vertex u to v. And weight
   // of the edge is w.
   int graph[][3] = { { 0, 1, -1 }, { 0, 2, 4 },
                      { 1, 2, 3 }, { 1, 3, 2 },
                      { 1, 4, 2 }, { 3, 2, 5 },
                      { 3, 1, 1 }, { 4, 3, -3 } };

   BellmanFord(graph, V, E, 0);
   return 0;
}
