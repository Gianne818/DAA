/*
Input, vertices
Given a graph, can we color it with HOW many colors minimum?

node with color sa struct
- Adjacency List Representation

*/

#include <iostream>
#include "graphcoloring.hpp"

using namespace std;

int main() {
    char op;
    char v;
    char u;
    char dest;
    int e;

    GraphColoringSolver graph;

    cout << "===== GRAPH COLORING SOLVER =====" << endl;
    cout << "Finds the MINIMUM number of colors needed." << endl;
    cout << endl;
    cout << "Commands:" << endl;
    cout << "  v <vertex>" << endl;
    cout << "     Insert vertex" << endl;
    cout << "     Example: v A" << endl;
    cout << endl;
    cout << "  e <u> <v> <id>" << endl;
    cout << "     Insert edge" << endl;
    cout << "     Example: e A B 1" << endl;
    cout << endl;
    cout << "  V <u> <v>" << endl;
    cout << "     Insert edge (auto ID = 1) & vertices" << endl;
    cout << "     Example: V A B" << endl;
    cout << endl;
    cout << "  p" << endl;
    cout << "     Print graph" << endl;
    cout << endl;
    cout << "  s" << endl;
    cout << "     Find minimum colors needed" << endl;
    cout << endl;
    cout << "  x" << endl;
    cout << "     Exit program" << endl;
    cout << "================================" << endl;

    do {
        cout << "Operation: ";
        cin >> op;

        switch (op) {
            case 'v':
                cin >> v;
                graph.insertVertex(v);
                cout << "Vertex " << v << " inserted." << endl;
                break;

            case 'V':
                cin >> u >> v;
                graph.insertVertex(u);
                graph.insertVertex(v);
                graph.insertEdge(u, v, 1);
                cout << "Edge inserted between " << u << " and " << v << "." << endl;
                break;

            case 'e':
                cin >> u >> dest >> e;
                graph.insertEdge(u, dest, e);
                cout << "Edge inserted between " << u << " and " << dest << "." << endl;
                break;

            case 'p':
                graph.printGraph();
                break;

            case 's':
                cout << endl;
                cout << "Finding minimum colors needed..." << endl;
                graph.printResult();
                break;

            case 'x':
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid operation!" << endl;
                cout << "Use only: v, e, V, p, s, x" << endl;
        }
    } while (op != 'x');

    return 0;
}
/*
Operation: V a b V a c V a d s
Edge inserted between a and b.
Operation: Edge inserted between a and c.
Operation: Edge inserted between a and d.
Operation: 
Finding minimum colors needed...

===== RESULT =====
Minimum colors needed: 2
Optimal coloring: { A=Red, B=Green, C=Green, D=Green }
*/