/*****************************************************************/
/* GraphL.cpp
/*
/* Author: Hans Nicolaus
/*
/* This file contains the implementations of the constructors and
/* methods which interfaces are defined in the GraphL.h file
/*
/*****************************************************************/

#include "graphl.h"
#include <limits>
#include <fstream>

/*
 Default constructor:
 Pre-condition: Sufficient memory is available.
 Post-condition: The adjacency list is initialized to point to NULL and the size is set to empty.
 */
GraphL::GraphL()
{
    size = 0;
    
    for(int i = 0; i < MAXNODES; i++)
    {
        adjacencyList[i] = NULL;
    }
}

/*
 buildGraph:
 Pre-condition: The file associated with the input stream exists.
                input is the input stream that allows working with the text file.
 Post-condition: The adjacency list is constructed with data read from the input text file. All vertices are marked as unvisited. The address that corresponds with each vertex is within the list.
 */
void GraphL::buildGraph(ifstream& input)
{
    input >> size;
    
    // move the cursor tp the next line, ignoring \n character after the last >>
    string discardEndline;
    getline(input, discardEndline);

    for(int i = 1; i <= size; i++)
    {
        // CLEAN UP
        // creating new graph node object
        adjacencyList[i] = new GraphNode();
        
        // filling in corresponding poi
        string str;
        getline(input, str);
        adjacencyList[i]->data = new NodeData(str);
        
        // setting all GraphNode to not visited
        adjacencyList[i]->visited = false;
        
        // setting all edgeHead to NULL, so that the Nodes without any adjacency is conditioned
        adjacencyList[i]->edgeHead = NULL;
    }

    int source = std::numeric_limits<int>::max();
    int dest = std::numeric_limits<int>::max();

    while((source != 0 || dest != 0) && !input.eof())
    {
        input >> source >> dest;
        if (source != 0 || dest != 0)
        {
            EdgeNode* temp = adjacencyList[source]->edgeHead;
            
            adjacencyList[source]->edgeHead = new EdgeNode();
            adjacencyList[source]->edgeHead->adjGraphNode = dest;
            
            adjacencyList[source]->edgeHead->nextEdge = temp;
        }
    }
    
    // move the cursor to the next line, ignoring \n character after the last >>
    getline(input, discardEndline);
}

/*
 depthFirstSearch:
 Pre-condition: The adjacency list is filled with information from the text file.
 Post-condition: The Nodes will be displayed in depth-first order on the console output after depth-first search is performed recursively.
 */
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering: ";
    
    // start depth-first search from the first vertex until the last one
    for(int v = 1; v <= size; v++)
    {
        // making sure that all vertices are visited when function ends
        if(!adjacencyList[v]->visited)
        {
            // calling recursive function to perform depth-first search
            DFS(v);
        }
    }
    
    cout << endl;
    cout << endl;
}

/*
 DFS:
 Pre-condition: idx is the next vertex to be ordered using depth-first search
 Post-condition: The vertex idx and all its adjacent vertices will be sorted in depth-first order and displayed on console output.
 */
void GraphL::DFS(int idx)
{
    // printing out each vertex made as source in depth-first order
    cout << idx << " ";
    // marking visited for the vertex
    adjacencyList[idx]->visited = true;
    EdgeNode* curr = adjacencyList[idx]->edgeHead;
    
    // keep on iterating until entire adjacent vertices of the source vertex is visited
    while(curr != NULL)
    {
        // calling itself (recursively) untill all adjacent vertices of a
        // source vertex is visited
        if(!adjacencyList[curr->adjGraphNode]->visited)
        {
            DFS(curr->adjGraphNode);
        }
        
        curr = curr->nextEdge;
    }
}

/*
 displayGraph:
 Pre-condition: The adjacency list is completed and contains correct information based on the text file.
 Post-condition: All information about each and every vertices will be displayed on the console output in an organized manner, which includes displaying all available edges between each and every source vertices with their adjacent vertices and the corresponding address of each source vertex.
 */
void GraphL::displayGraph()
{
    cout << "----------------------------------------" << endl;
    cout << "Graph:" << endl;
    cout << "----------------------------------------" << endl;
    
    for(int source = 1; source <= size; source++)
    {
        cout << "Node " << source << "    " << *(adjacencyList[source]->data) <<endl;
        cout << "----------------------------------------" << endl;
        
        EdgeNode* temp = adjacencyList[source]->edgeHead;
        while(temp != NULL)
        {
            cout << " edge " << source << " " <<temp->adjGraphNode << endl;
            
            temp = temp->nextEdge;
        }
	
	if(source != size)
	{
		cout << "========================================" << endl;
	}
	else
	{
		cout << "----------------------------------------" << endl;
	}
    }
    
    cout << endl;
}

/*
 ~GraphL:
 Pre-condition: GraphL is located in a function that is going out of scope.
 Post-condition: All memory previously allocated for the GraphL is deallocated.
 */
GraphL::~GraphL()
{
    for(int i = 1; i <= size; i++)
    {
        // calling delete for all EdgeNode pointer by EdgeHead
        while(adjacencyList[i]->edgeHead != NULL)
        {
            EdgeNode* temp = adjacencyList[i]->edgeHead->nextEdge;
            
            adjacencyList[i]->edgeHead->nextEdge = NULL;
            delete adjacencyList[i]->edgeHead;
            
            adjacencyList[i]->edgeHead = temp;
        }
        
        // deleting the nodedata pointer that contains the corresponding
        // address to the vertex
        delete adjacencyList[i]->data;
        adjacencyList[i]->data = NULL;

        // calling delete for the GraphNode in the list indices
        delete adjacencyList[i];
        adjacencyList[i] = NULL;
    }
}
