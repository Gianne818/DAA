#include <iostream>
#include "hamiltoniancycle.hpp"
using namespace std;

int main() {
    char op;
    char v;
    char u;
    char dest;
    int e;

    HamiltonianCycleSolver graph;

    cout << "===== HAMILTONIAN CYCLE SOLVER =====" << endl;
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
    cout << "     Find Hamiltonian cycle" << endl;
    cout << "     Example: s" << endl;
    cout << endl;
    cout << "  x" << endl;
    cout << "     Exit program" << endl;
    cout << "===================================" << endl;

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
                cout << "Finding Hamiltonian cycle..." << endl;
                if (graph.solve()) {
                    cout << "Hamiltonian cycle found!" << endl;
                    graph.printCycle();
                } else {
                    cout << "No Hamiltonian cycle exists." << endl;
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
Operation: V a b V b c V c d V d a
Edge inserted between a and b.
Operation: Edge inserted between b and c.
Operation: Edge inserted between c and d.
Operation: Edge inserted between d and a.
Operation: [
Invalid operation!
Use only: v, e, V, p, s, x
Operation: s

Finding Hamiltonian cycle...
Hamiltonian cycle found!
Hamiltonian Cycle: a -> b -> c -> d -> a
Operation: V d e
Edge inserted between d and e.
Operation: p

===== GRAPH (Adjacency List) =====
a -> b, d
b -> a, c
c -> b, d
d -> c, a, e
e -> d
Vertices: 5
Operation: s

Finding Hamiltonian cycle...
No Hamiltonian cycle exists.

Note: Graph has vertex e as leaf (degree 1), so Hamiltonian cycle impossible.


*/