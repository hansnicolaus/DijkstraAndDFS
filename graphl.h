/*****************************************************************/
/* GraphL.h
/*
/* Author: Hans Nicolaus
/*
/* This header file contains the interfaces of method implementations
/* of the GraphL class, which hides the implementations
/* of all methods that are implemented in the GraphL.cpp file.
/*
/*****************************************************************/

#ifndef GRAPHL_H
#define GRAPHL_H
#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

class GraphL
{
public:
    /*
     Default constructor:
     Pre-condition: Sufficient memory is available.
     Post-condition: The adjacency list is initialized to point to NULL and the size is set to empty.
     */
    GraphL();
    
    /*
     buildGraph:
     Pre-condition: The file associated with the input stream exists.
                    input is the input stream that allows working with the text file.
     Post-condition: The adjacency list is constructed with data read from the input text file. All vertices are marked as unvisited. The address that corresponds with each vertex is within the list.
     */
    void buildGraph(ifstream& input);
    
    /*
     depthFirstSearch:
     Pre-condition: The adjacency list is filled with information from the text file.
     Post-condition: The Nodes will be displayed in depth-first order on the console output after depth-first search is performed recursively.
     */
    void depthFirstSearch();
    
    /*
     displayGraph:
     Pre-condition: The adjacency list is completed and contains correct information based on the text file.
     Post-condition: All information about each and every vertices will be displayed on the console output in an organized manner, which includes displaying all available edges between each and every source vertices with their adjacent vertices and the corresponding address of each source vertex.
     */
    void displayGraph();
    
    /*
     ~GraphL:
     Pre-condition: GraphL is located in a function that is going out of scope.
     Post-condition: All memory previously allocated for the GraphL is deallocated.
     */
    ~GraphL();
    
private:
    /*
     DFS:
     Pre-condition: idx is the next vertex to be ordered using depth-first search
     Post-condition: The vertex idx and all its adjacent vertices will be sorted in depth-first order and displayed on console output.
     */
    void DFS(int idx);
    
    struct EdgeNode;      // forward reference for the compiler
    
    /*
     Node: a private struct that serves as a node in the BinTree object. Each
     contains a NodeData pointer that points to a NodeData object that contains
     a string as the data that are held in the BinTree object.
     */
    struct GraphNode {    // structs used for simplicity, use classes if desired
        
        EdgeNode* edgeHead; // head of the list of edges
        
        NodeData* data;     // data information about each node
        
        bool visited;
        
    };
 
    /*
     EdgeNode: a private struct that serves as a node in the GraphNode. Each
     contains a NodeData pointer that points to a NodeData object that contains
     a string as the data that are held in the BinTree object.
     */
    struct EdgeNode {
        
        int adjGraphNode;  // subscript of the adjacent graph node
        
        EdgeNode* nextEdge; // pointer to the next adjacent node
        
    };
  
    const static int MAXNODES = 100;
        
    GraphNode* adjacencyList[MAXNODES]; // array of pointers to store node adjacency
        
    int size;                             // number of nodes in the graph
    
};

#endif
