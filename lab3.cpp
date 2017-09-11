/*****************************************************************/
/* lab3.cpp
/*
/* Author: Hans Nicolaus
/*
/* This driver file contains codes to test the implementations of
/* GraphM and GraphL methods, to ensure that they behave properly and
/* produces the correct and desirable output.
/*
/*****************************************************************/

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
using namespace std;

int main() {
	
	// part 1
	ifstream infile1("data31.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes
	for (;;){
    GraphM G;
		G.buildGraph(infile1);
        if (infile1.eof())
			break;
		G.findShortestPath();
		G.displayAll();              // display shortest distance, path to cout
		G.display(3, 1);             // display path from node 3 to 1 to cout
		G.display(1, 2);
		G.display(1, 4);
        
        cout << endl;
        
        G.insertEdge(1, 3, 20); // inserting edge that existed before for first graph
        G.insertEdge(6, 1, 60); // inserting edge with invalid source vertex
        G.insertEdge(1, 2, 30); // changing pre-existing edge with insert method
        G.insertEdge(-1, 4, 60); // inserting edge with negative values for source vertex.
        G.insertEdge(1, -4, 60); // inserting edge with negative values for destination vertex.
        
        G.removeEdge(-1, 6); // removing invalid source and destination vertex
        G.removeEdge(1, 3); // removing pre-existing edge
        G.removeEdge(1, 2); // removing valid edge (for graph 1)
        
        G.findShortestPath(); // re-computing shortest paths and distances after inserting and removing several edges
        G.displayAll(); // re-printing the output
        
        cout << endl;
    }
	
	// part 2
	ifstream infile2("data32.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile2);
		if (infile2.eof())
			break;
		G.displayGraph();
		G.depthFirstSearch();    // find and display depth-first ordering to cout
	}
//	
	return 0;
}
