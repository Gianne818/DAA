/*

Find shortest possible route that visits every vertex exactly once and returns to start (Hamiltonian cycle with minimum cost).

Hamiltonian cycle = visits every vertex exactly once and returns to start.

*/
#include <iostream>
#include "graphmatrix.hpp"
using namespace std;

int main(void) {
    char op;
    int v, x, orig, dest, e;
    int num, i, start;
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

    // Connect isolated vertices 8 and 9, and ensure connectivity
    graph->insertEdge(6, 8, 5);  // Connect 6 to 8
    graph->insertEdge(6, 9, 4);  // Connect 6 to 9
    graph->insertEdge(8, 9, 3);  // Connect 8 to 9
    graph->insertEdge(7, 8, 7);  // Connect 7 to 8 (7 was connected only to 3)
    graph->insertEdge(9, 0, 8);  // Connect 9 back to start for cycle
    graph->insertEdge(7, 9, 6);  // Alternative path for 7
    graph->insertEdge(1, 8, 5);  // Connect 1 to 8 for more options

    graph->print();
    
    do {
        cout << "Operation: ";
        cin >> op;
        switch (op) {
            case 'v':
                cin >> v;
                graph->insertVertex(v);
                break;
            case 'e':
                cin >> orig >> dest >> e;
                graph->insertEdge(orig, dest, e);
                break;
            case 'p':
                graph->print();
                break;
            case 's':
                cin >> orig >> dest;
                cout << graph->distance(orig, dest) << endl;
                break;
            case 'T': // TSP Branch and Bound
                graph->solveTSP();
                break;
            case 't':
                cin >> start;
                graph->solveTSP(start);
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