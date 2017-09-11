/*****************************************************************/
/* GraphM.cpp
/*
/* Author: Hans Nicolaus
/*
/* This file contains the implementations of the constructors and
/* methods which interfaces are defined in the GraphM.h file
/*
/*****************************************************************/

#include "graphm.h"
#include <limits>
#include <fstream>

/*
 Default constructor:
 Pre-condition: Sufficient memory is available.
 Post-condition: Data members of shortest path matrix and adjacency matrix are initialized to their default values (values prior to assigning any graph information)
 */
GraphM::GraphM()
{
    for(int row = 0; row < MAXNODES; row++)
    {
        for(int col = 0; col < MAXNODES; col++)
        {
            T[row][col].visited = false;
            T[row][col].dist = std::numeric_limits<int>::max();
            T[row][col].path = 0;
            
            C[row][col] = std::numeric_limits<int>::max();
        }
    }
    
    size = 0;
}

/*
 buildGraph:
 Pre-condition: The file associated with the input stream exists.
                input is the input stream that allows working with the text file.
 Post-condition: The adjacency matrix is filled with data read from the input text file.
 */
void GraphM::buildGraph(ifstream& input)
{
    input >> size;
    
    // move the cursor tp the next line, ignoring \n character after the last >>
    string discardEndline;
    getline(input, discardEndline);
    
    for(int i = 1; i <= size; i++)
    {
        data[i].setData(input);
    }
    
    int source = std::numeric_limits<int>::max();
    int dest = std::numeric_limits<int>::max();
    int dist = std::numeric_limits<int>::max();
    while((source != 0 || dest != 0 || dist != 0) && !input.eof())
    {
        input >> source >> dest >> dist;
        if (source != 0 || dest != 0 || dist != 0)
        {
            insertEdge(source, dest, dist);
        }
    }
    
    // move the cursor to the next line, ignoring \n character after the last >>
    getline(input, discardEndline);
}

/*
 insertEdge:
 Pre-condition: The source and destination vertex are valid.
                source is the vertex where the edge starts from.
                dest is the vertex where the edge ends at.
                weight is the distance between source and destination vertex.
 Post-condition: The distance (weight) between the source and destination vertex in the adjacency matrix is updated with the desired distance (weight). If the edge already existed, weight for it will be changed if the desired weight is different.
 */
void GraphM::insertEdge(int source, int dest, int weight)
{
    if(source < 1 || dest < 1)
    {
        cout << "Edge failed to be inserted. Please provide valid input." << endl;
        cout << endl;
    }
    else
    {
        if(C[source][dest] != weight)
        {
            if(source >= 1 && source <= size && dest >= 1 && dest <= size && source != dest)
            {
                C[source][dest] = weight;
            }
            else
            {
                cout << "Edge failed to be inserted. Please provide valid input." << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "Edge already existed. Same edges will not be inserted again." << endl;
            cout << endl;
        }
    }
}

/*
 removeEdge:
 Pre-condition: The source and destination vertex are valid.
                source is the vertex where the edge starts from.
                dest is the vertex where the edge ends at.
 Post-condition: The distance between the source and destination vertex in the adjacency matrix is set to infinite, which indicates that the source vertex no longer has a path towards the destination vertex.
 */
void GraphM::removeEdge(int source, int dest)
{
    if(source >= 1 && source <= size && dest >= 1 && dest <= size && source != dest)
    {
        C[source][dest] = std::numeric_limits<int>::max();
        cout << "The following edge is removed: " << source << "->" << dest;
        cout << ". Please recompute shortest paths and distances";
        cout << " to get the updated shortest paths and distances." << endl;
        cout << endl;
    }
    else
    {
        cout << "No edge is removed. Please provide valid input." << endl;
        cout << endl;
    }
}

/*
 findV:
 Pre-condition: source is the source vertex.
                vCheck is the vertex to be checked if it is the next vertex to be visited and to be compared with the source vertex, then marked as visited to avoid repeated comparison between source vertex and that vertex again.
                min is the current minimum distance between the source vertex and the compared vertex.
 Post-condition: The vertex to be compared next with the source vertex is returned.
 */
int GraphM::findV(int source, int vCheck, int& min)
{
    if(vCheck == 1)
    {
        // comparing the source vertex with itself for every first comparison
        T[source][source].visited = true;
        min = 0;
        return source;
    }
    else
    {
        bool found = false;
        int tempMin = 0;
        
        // finding a temporary unvisited vertex as temporary minimum
        for(int i = 1; i <= size && found == false; i++)
        {
            if(!T[source][i].visited && T[source][i].dist != std::numeric_limits<int>::max())
            {
                tempMin = T[source][i].dist;
                found = true;
            }
        }

        if(found == true)
        {
            // finding the next minimum (unvisited & smaller than temporary minimum)
            for(int i = 1; i <= size; i++)
            {
                if(!T[source][i].visited && T[source][i].dist <= tempMin && T[source][i].dist != std::numeric_limits<int>::max())
                {
                    min = T[source][i].dist;
                    tempMin = min;
                }
            }
        }
        
        for(int vIdx = 1; vIdx <= size; vIdx++)
        {
            if(min == T[source][vIdx].dist)
            {
                T[source][vIdx].visited = true;
                return vIdx;
            }
        }
        // just so control path does not reach end of non-void
        return 0;
    }
}

/*
 findShortestPath:
 Pre-condition: The adjacency matrix is filled with information from the text file.
 Post-condition: The shortest path matrix will be filled with the shortest distances between all vertices to all corresponding adjacent vertices by using Dijkstra algorithm. For each distance in the shortest distance matrix, one vertex that comes before the destination vertex is stored.
 */
void GraphM::findShortestPath()
{
    for(int row = 0; row < MAXNODES; row++)
    {
        for(int col = 0; col < MAXNODES; col++)
        {
            T[row][col].visited = false;
            T[row][col].dist = std::numeric_limits<int>::max();
            T[row][col].path = 0;
        }
    }
    
    for (int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        int min = T[source][source].dist;
        
        // finds the shortest distance from source to all other nodes
        for (int vCheck = 1; vCheck <= size; vCheck++)
        {
            // find v not visited, shortest distance at this point & mark v visited
            int v = findV(source, vCheck, min);

            // for each w adjacent to v
            for(int w = 1; w <= size; w++)
            {
                if(C[v][w] != std::numeric_limits<int>::max() && !T[source][w].visited)
                {
                    // if (w is not visited)
                    if(T[source][w].dist > T[source][v].dist+C[v][w])
                    {
                        T[source][w].dist = T[source][v].dist+C[v][w];
                        T[source][w].path = v;
                    }
                }
            }
        }
        min = 0;
    }
}

/*
 shortestPath:
 Pre-condition: source is the source vertex.
                dest is the destination vertex.
 Post-condition: All visited vertices that generates the shortest travel distance between the source and the destination vertex is displayed on console output.
 */
void GraphM::shortestPath(int source, int dest)
{
    if(source >= 1 && source <= size && dest >= 1 && dest <= size && source != dest)
    {
        int pathReverse[size];
        for(int i = 1; i <= size; i++)
        {
            pathReverse[i] = 0;
        }
        if(source != dest)
        {
            int i = 1;
            pathReverse[i] = dest;
            i++;
            int temp = dest;
        
            while(temp != source)
            {
                pathReverse[i] = T[source][temp].path;
                i++;
                temp = T[source][temp].path;
            }
        }
        for(int i = size; i >= 1; i--)
        {
            if(pathReverse[i] != 0)
            {
                cout << pathReverse[i] << " ";
            }
        }
    }
    else
    {
        cout << "Invalid input vertices, shortest path unavailable." << endl;
    }
}

/*
 displayAll:
 Pre-condition: The shortest path matrix is completed and contains correct information based on the adjacency matrix.
 Post-condition: All information about each and every vertices will be displayed on the console output in an organized manner, which includes displaying the shortest distance and path between all source vertices with their adjacent vertices and the corresponding address of each source vertices.
 */
void GraphM::displayAll()
{
    cout << "-------------------------------------------------------------" << endl;
    cout << "Description           From_node  To_node  Dijkstra's  Path" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for(int source = 1; source <= size; source++)
    {
        cout << data[source] << endl;
        cout << "-------------------------------------------------------------" << endl;
        for(int dest = 1; dest <= size; dest++)
        {
            if(source != dest)
            {
                if(T[source][dest].path != 0)
                {
                    cout << "                          " << source << "         " << dest << "         " << T[source][dest].dist << "      ";
                    shortestPath(source, dest);
                    cout <<endl;
                }
                else
                {
                    cout << "                          " << source << "         " << dest << "         " << "----" <<  endl;
                }
            }
        }
        if(source != size)
        {
            cout << "=============================================================" << endl;
        }
        else
        {
            cout << "-------------------------------------------------------------" << endl;
        }
        
    }
}

/*
 displayPath:
 Pre-condition: source is the source vertex.
                dest is the destination vertex.
 Post-condition: The address for all visited vertices that generates the shortest travel distance between the source and the destination vertex is displayed on console output.
 */
void GraphM::displayPath(int source, int dest)
{
    if(T[source][dest].dist != std::numeric_limits<int>::max())
    {
        int arraySize = 0;
    
        if(source != dest)
        {
            arraySize++;
            int temp = dest;
        
            while(temp != source)
            {
                arraySize++;
                temp = T[source][temp].path;
            }
        }
    
        int array[arraySize];
    
        array[1] = dest;
        int temp = dest;
    
        int i = 2;
        while(temp != source)
        {
            array[i] = T[source][temp].path;
            temp = T[source][temp].path;
            i++;
        }
    
        for(int idx = arraySize; idx >= 1; idx--)
        {
            cout << data[array[idx]] << endl;
        }
        cout << endl;
    }
    else
    {
        cout << endl;
    }
}

/*
 display:
 Pre-condition: source is the source vertex.
                dest is the destination vertex.
 Post-condition: The source vertex, destination vertex, the shortest travel distance, the vertices travelled to reach destination vertex from source vertex that generates the shortest distance, and the corresponding address for all that vertices are displayed on console output.
 */
void GraphM::display(int source, int dest)
{
    if(source >= 1 && source <= size && dest >= 1 && dest <= size && T[source][dest].path != 0)
    {
        cout << source << "       " << dest << "      " << T[source][dest].dist << "          ";
        shortestPath(source, dest);
        cout << endl;
        displayPath(source, dest);
    }
    else
    {
        cout << source << "       " << dest << "      " << "----" <<  endl;
        cout << endl;
    }
}
