/* 

 https://www.cs.usfca.edu/~galles/visualization/Dijkstra.html
 Undirected Graph
 Adjacency Matrix Representation
 Dijkstra's
 - Returns shortest path distance (sum of edge weights) from orig to dest.
*/

#include <iostream>
#include "graphmatrix.hpp"
using namespace std;

int main(void) {
    char op;

    int v, x;
    int orig, dest;
    int e;

    int num, i;
    char* verts;
    int* edges;
    Graph* graph = new GraphMatrix();
    
    // Insert all vertices first (0-9)
    for (int i = 0; i <= 9; i++) {
        graph->insertVertex(i);
    }

    graph->insertEdge(0, 2, 4);
    graph->insertEdge(0, 4, 2);
    graph->insertEdge(1, 2, 8);
    graph->insertEdge(1, 5, 9);
    graph->insertEdge(2, 4, 9);
    graph->insertEdge(2, 5, 7);
    graph->insertEdge(2, 6, 6);
    graph->insertEdge(3, 0, 2);
    graph->insertEdge(3, 5, 2);
    graph->insertEdge(3, 7, 6);
    graph->insertEdge(4, 6, 9);
    graph->insertEdge(5, 6, 6);
    graph->print();
    
    do {
        cout << "Operation: ";
        cin >> op;
        switch (op) {
            case 'd': 
                cin >> orig;
                cin >> dest;
                cout << graph->dijkstra(orig, dest) << endl;
                break;
            case 'v':
                cin >> v;
                graph->insertVertex(v);
                break;
            case 'e':
                cin >> orig;
                cin >> dest;
                cin >> e;
                graph->insertEdge(orig, dest, e);
                // comment/uncomment depends if directional or undirectional
                // graph->insertEdge(dest, orig, e); // for undirectional graphs
                break;
            case 'p':
                graph->print();
                break;
            case 's':
                cin >> orig;
                cin >> dest;
                cout << graph->distance(orig, dest) << endl;
                break;
            case 'x':
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');

    return 0;
}