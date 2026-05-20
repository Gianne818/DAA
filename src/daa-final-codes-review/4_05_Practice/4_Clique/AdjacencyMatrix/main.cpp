#include <iostream>
#include "clique.hpp"

using namespace std;

int main() {
    char op;
    char v;
    char u;
    char dest;
    int e;
    int k;

    CliqueSolver graph;

    cout << "===== CLIQUE SOLVER (Adjacency Matrix) =====" << endl;
    cout << "Commands:" << endl;
    cout << "  v <vertex>" << endl;
    cout << "     Insert vertex" << endl;
    cout << "     Example: v a" << endl;
    cout << endl;
    cout << "  e <u> <v> <id>" << endl;
    cout << "     Insert edge" << endl;
    cout << "     Example: e a b 1" << endl;
    cout << endl;
    cout << "  V <u> <v>" << endl;
    cout << "     Insert edge (auto ID = 1) & vertices" << endl;
    cout << "     Example: V a b" << endl;
    cout << endl;
    cout << "  p" << endl;
    cout << "     Print graph" << endl;
    cout << endl;
    cout << "  s <k>" << endl;
    cout << "     Find clique of size k" << endl;
    cout << "     Example: s 3" << endl;
    cout << endl;
    cout << "  x" << endl;
    cout << "     Exit program" << endl;
    cout << "============================================" << endl;

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
                cin >> k;
                cout << endl;
                cout << "Finding clique of size " << k << "..." << endl;
                if (graph.solve(k)) {
                    cout << "Clique found!" << endl;
                    graph.printClique();
                } else {
                    cout << "No clique of size " << k << " exists." << endl;
                }
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
Operation: V b c
Edge inserted between b and c.
Operation: V a f
Edge inserted between a and f.
Operation: V b a
Edge inserted between b and a.
Operation: V c f
Edge inserted between c and f.
Operation: V b f
Edge inserted between b and f.
Operation: V a c
Edge inserted between a and c.
Operation: V c d
Edge inserted between c and d.
Operation: V f e
Edge inserted between f and e.
Operation: V d e
Edge inserted between d and e.
Operation: p

===== GRAPH (Adjacency Matrix) =====
    a b c d e f
 a 0 1 1 0 0 1 
 b 1 0 1 0 0 1 
 c 1 1 0 1 0 1 
 d 0 0 1 0 1 0 
 e 0 0 0 1 0 1 
 f 1 1 1 0 1 0 
Vertices: 6
Operation: s 4

Finding clique of size 4...
Clique found!
Clique: { a, b, c, f }
*/