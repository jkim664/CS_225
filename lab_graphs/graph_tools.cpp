/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{	
	
	return -1;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	Vertex v = graph.getStartingVertex();
	
	Edge curr_min;
	
	queue<Vertex> q;
	
	int min = -1;
	
	graph.setVertexLabel(v, "VISITED");
	
	q.push(v);
	
	
	while (!q.empty()) {
		
		v = q.front();
		
		q.pop();
		
		vector<Vertex> adj = graph.getAdjacent(v);
		
		for (int i = 0; i < adj.size(); i++) {
		
			if ( graph.getVertexLabel(adj[i]) != "VISITED") {
			
				if (min == -1) {
					min = graph.getEdgeWeight(v, adj[i]);
					curr_min = graph.getEdge(v, adj[i]);
					
				}
				
				else if (graph.getEdgeWeight(v, adj[i]) < min) {
				
					min = graph.getEdgeWeight(v, adj[i]);
					curr_min = graph.getEdge(v, adj[i]);
					
				}
			
				graph.setVertexLabel(adj[i], "VISITED");
				//graph.setEdgeLabel(v, adj[i], "DISCOVERY");
				q.push(adj[i]);
			
			}
			
			else {
				if (min == -1) {
					min = graph.getEdgeWeight(v, adj[i]);
					curr_min = graph.getEdge(v, adj[i]);
					
				}
				
				else if (graph.getEdgeWeight(v, adj[i]) < min) {
				
					min = graph.getEdgeWeight(v, adj[i]);
					curr_min = graph.getEdge(v, adj[i]);
					
				}
				
				//graph.setEdgeLabel(v, adj[i], "CROSS");
			
			}
			
		}
	
	
	}
	
	graph.setEdgeLabel(curr_min.source, curr_min.dest, "MIN");

	return min;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector<Vertex> V = graph.getVertices();
	vector<Edge> E = graph.getEdges();
	queue<Edge> Q;
	vector<Edge> A;
	DisjointSets DS;
	
	
	
	for(int i=0; i< E.size(); i++) {
		Q.push(E[i]);
	}
	
	
	DS.addelements(V.size());
		
	sort(E.begin(), E.end());
	
	for (int i=0; i < E.size(); i++) {
		
		if(DS.find(E[i].source) != DS.find(E[i].dest)) {
			
			A.push_back(E[i]);
			
			graph.setEdgeLabel(E[i].source, E[i].dest, "MST");
			
			DS.setunion(E[i].source, E[i].dest);
		}
	}

}





