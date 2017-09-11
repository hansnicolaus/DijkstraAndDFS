/*****************************************************************/
/* GraphM.h
/*
/* Author: Hans Nicolaus
/*
/* This header file contains the interfaces of method implementations
/* of the GraphM class, which hides the implementations
/* of all methods that are implemented in the GraphM.cpp file.
/*
/*****************************************************************/

#ifndef GRAPHM_H
#define GRAPHM_H
#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

class GraphM
{
public:
    /*
     Default constructor:
     Pre-condition: Sufficient memory is available.
     Post-condition: Data members of shortest path matrix and adjacency matrix are initialized to their default values (values prior to assigning any graph information)
     */
    GraphM();
    
    /*
     buildGraph:
     Pre-condition: The file associated with the input stream exists.
     input is the input stream that allows working with the text file.
     Post-condition: The adjacency matrix is filled with data read from the input text file.
     */
    void buildGraph(ifstream& input);
    
    /*
     insertEdge:
     Pre-condition: The source and destination vertex, and their weight are valid.
     source is the vertex where the edge starts from.
     dest is the vertex where the edge ends at.
     weight is the distance between source and destination vertex.
     Post-condition: The distance (weight) between the source and destination vertex in the adjacency matrix is updated with the desired distance (weight).
     */
    void insertEdge(int source, int dest, int weight);
    
    /*
     removeEdge:
     Pre-condition: The source and destination vertex are valid.
                    source is the vertex where the edge starts from.
                    dest is the vertex where the edge ends at.
     Post-condition: The distance between the source and destination vertex in the adjacency matrix is set to infinite, which indicates that the source vertex no longer has a path towards the destination vertex.
     */
    void removeEdge(int source, int dest);
    
    /*
     findShortestPath:
     Pre-condition: The adjacency matrix is filled with information from the text file.
     Post-condition: The shortest path matrix will be filled with the shortest distances between all vertices to all corresponding adjacent vertices by using Dijkstra algorithm. For each distance in the shortest distance matrix, one vertex that comes before the destination vertex is stored.
     */
    void findShortestPath();
    
    /*
     displayAll:
     Pre-condition: The shortest path matrix is completed and contains correct information based on the adjacency matrix.
     Post-condition: All information about each and every vertices will be displayed on the console output in an organized manner, which includes displaying the shortest distance and path between all source vertices with their adjacent vertices and the corresponding address of each source vertices.
     */
    void displayAll();
    
    /*
     display:
     Pre-condition: source is the source vertex.
     dest is the destination vertex.
     Post-condition: The source vertex, destination vertex, the shortest travel distance, the vertices travelled to reach destination vertex from source vertex that generates the shortest distance, and the corresponding address for all that vertices are displayed on console output.
     */
    void display(int source, int dest);

private:
    /*
     displayPath:
     Pre-condition: source is the source vertex.
     dest is the destination vertex.
     Post-condition: The address for all visited vertices that generates the shortest travel distance between the source and the destination vertex is displayed on console output.
     */
    void displayPath(int source, int dest);
    
    /*
     shortestPath:
     Pre-condition: source is the source vertex.
     dest is the destination vertex.
     Post-condition: All visited vertices that generates the shortest travel distance between the source and the destination vertex is displayed on console output.
     */
    void shortestPath(int source, int dest);
    
    /*
     findV:
     Pre-condition: The Polynomial object exists.
     source is the source vertex.
     vCheck is the vertex to be checked if it is the next vertex to be visited and to be compared with the source vertex, then marked as visited to avoid repeated comparison between source vertex and that vertex again.
     min is the current minimum distance between the source vertex and the compared vertex.
     Post-condition: The vertex to be compared next with the source vertex is returned.
     */
    int findV(int source, int vCheck, int& min);
    
    /*
     Node: a private struct that serves as a node in the BinTree object. Each
     contains a NodeData pointer that points to a NodeData object that contains
     a string as the data that are held in the BinTree object.
     */
    struct TableType
    {
        bool visited;          // whether node has been visited
        
        int dist;              // shortest distance from source known so far
        
        int path;              // previous node in path of min dist
        
    };

    const static int MAXNODES = 100;      // maximum number of nodes possible
    
    NodeData data[MAXNODES];              // data for graph nodes
    
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    
    int size;                             // number of nodes in the graph
    
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
};

#endif
