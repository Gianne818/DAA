// main.cpp

#include <iostream>
#include "vertexcover.hpp"

using namespace std;

int main() {
    char op;
    char v;
    char u;
    char dest;
    int e;
    int k;

    VertexCoverSolver graph;

    cout << "===== VERTEX COVER SOLVER =====" << endl;
    cout << "Commands:" << endl;
    cout << "  v <vertex>" << endl;
    cout << "     Insert vertex" << endl;
    cout << "     Example: v A" << endl;
    cout << endl;
    cout << "  e <u> <v> <id>" << endl;
    cout << "     Insert edge" << endl;
    cout << "     Example: e A B 1" << endl;
    cout << endl;
    cout << "  p" << endl;
    cout << "     Print graph" << endl;
    cout << endl;
    cout << "  s <k>" << endl;
    cout << "     Solve Vertex Cover" << endl;
    cout << "     Example: s 2" << endl;
    cout << endl;
    cout << "  x" << endl;
    cout << "     Exit program" << endl;
    cout << "===============================" << endl;

    do {
        cout << "\nOperation: ";
        cin >> op;

        switch (op) {
            case 'v':
                cin >> v;
                graph.insertVertex(v);
                cout << "Vertex " << v << " inserted." << endl;
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
                cin >> k;
                cout << endl;
                cout << "Solving Vertex Cover with k = " << k << "..." << endl;
                if (graph.solve(k)) {
                    cout << "Solution found!" << endl;
                    graph.printCover();
                } else {
                    cout << "No vertex cover of size " << k << " exists." << endl;
                }
                break;

            case 'x':
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid operation!" << endl;
                cout << "Use only: v, e, p, s, x" << endl;
        }
    } while (op != 'x');

    return 0;
}
/*
===== GRAPH =====
A -> B
B -> A, D
C -> D
D -> B, C, E
E -> D, F
F -> E
Vertices: 6
Edges: 5

Operation: s 3

Solving Vertex Cover with k = 3...
Solution found!
Vertex Cover: { A, D, E }

Note: Every edge has at least one endpoint in {A, D, E}.


*/