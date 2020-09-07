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
    queue<Vertex> myQ;
    myQ.push(start);
    vector<Vertex> allVertices = graph.getVertices();
    for (size_t i = 0; i < allVertices.size(); i++)
        graph.setVertexLabel(allVertices[i], "UNEXPLORED");
    graph.setVertexLabel(start, "VISITED");
    while(!myQ.empty()) {
        Vertex myTop = myQ.front();
        myQ.pop();
        if(myTop == end)
            break;
        vector<Vertex> myVertices =  graph.getAdjacent(myTop);
        for (size_t i = 0; i < myVertices.size(); i++) 
            if(graph.getVertexLabel(myVertices[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(myTop, myVertices[i], "DISCOVERY");
                graph.setVertexLabel(myVertices[i], "VISITED");
                myQ.push(myVertices[i]);
            
        
        }
    }
    int length = 0;
    Vertex parent = end;
    while(parent != start) {
        length++;
        vector<Vertex> goBack = graph.getAdjacent(parent);
        for (size_t i = 0; i < goBack.size(); i++)
            if(graph.getEdgeLabel(parent, goBack[i]) == "DISCOVERY") {
                //cout<< "this?"<<endl;
                graph.setEdgeLabel(parent, goBack[i], "MINPATH");       
                //cout<< "idk"<<endl;
                parent = goBack[i];
                break;
            }
    } 
    return length;
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
    int min = INT_MAX;
    Vertex u;
    Vertex v;
    queue<Vertex> myQ;
    Vertex start = graph.getStartingVertex();
    vector<Vertex> allVertices = graph.getVertices();
    for (size_t i = 0; i < allVertices.size(); i++)
        graph.setVertexLabel(allVertices[i], "UNEXPLORED");
    graph.setVertexLabel(start, "VISITED");
    vector<Edge> allEdges = graph.getEdges();
    //for (size_t i = 0; i < allEdges.size(); i++)
    //    allEdges[i].label = "UNEXPLORED";
    myQ.push(start);
    while(!myQ.empty()) {
        Vertex myTop = myQ.front();
        myQ.pop();
        vector<Vertex> myVertices =  graph.getAdjacent(myTop    );
        for (size_t i = 0; i < myVertices.size(); i++) {
            if(graph.getVertexLabel(myVertices[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(myTop, myVertices[i], "DISCOVERY");
                graph.setVertexLabel(myVertices[i], "VISITED");
                myQ.push(myVertices[i]);
            }
            if(graph.getEdgeWeight(myTop, myVertices[i]) < min) {
                        min = graph.getEdgeWeight(myTop, myVertices[i]);
                        u = myTop;
                        v = myVertices[i];
            }       
        }
    }
    graph.setEdgeLabel(u, v, "MIN");
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
    vector<Edge> myEdges = graph.getEdges();
    sort(myEdges.begin(), myEdges.end());
    DisjointSets myVertices;
    vector<Vertex> allVertices = graph.getVertices();
    int n = allVertices.size();
    myVertices.addelements(n);
    int count = 0;
    for (size_t i = 0; i < myEdges.size(); i++) {
        Vertex u = myEdges[i].source;
        Vertex v = myEdges[i].dest;
        int a = find(allVertices.begin(), allVertices.end(), u) - allVertices.begin();
        int b = find(allVertices.begin(), allVertices.end(), v) - allVertices.begin(); 
        if(myVertices.find(a) != myVertices.find(b)) {
            count++;
            myVertices.setunion(a, b);
            graph.setEdgeLabel(u, v, "MST");
        }
        if(count == n - 1)
            break;
    }
}
