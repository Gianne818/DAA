/* no idea if locked bato
 shortest possible path starting from a Vertex
 graph is unweighted DAW? we are still unsure, but doesnt make sense if ingon ana (ma 1 for all edges...)

 https://www.cs.usfca.edu/~galles/visualization/Dijkstra.html
 Undirected Graph
 Adjacency Matrix Representation
 
*/

#include <iostream>
#include "graphmatrix.hpp"
using namespace std;

int main(void) {
    char op, v, x;
    char orig, dest;
    int e;

    int num, i;
    char* verts;
    int* edges;
    Graph* graph = new GraphMatrix();
    
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