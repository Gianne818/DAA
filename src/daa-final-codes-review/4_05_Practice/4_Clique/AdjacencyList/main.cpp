// main.cpp

/*
Informal problem: Given a graph and an integer k, decide whether there is a subset of k vertices that are all pairwise adjacent (a k-clique).

Natural C++ representation: Use an adjacency list (vector<vector<int>>) or an adjacency matrix (vector<vector<bool>>) for faster edge checks. Vertices can be labeled 0..n−1.

Backtracking idea: Maintain a current candidate set of vertices. At each step, either include or exclude a vertex, ensuring that the included set remains a clique (every pair must be connected). Prune when the remaining vertices cannot possibly reach size k.

Representation: 

*/

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

    cout << "===== CLIQUE SOLVER =====" << endl;
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
    cout << "  s <k>" << endl;
    cout << "     Find clique of size k" << endl;
    cout << "     Example: s 3" << endl;
    cout << endl;
    cout << "  x" << endl;
    cout << "     Exit program" << endl;
    cout << "===============================" << endl;

    // User's vertex is a Character, don't mind the data type here...

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
                cout << "Use only: v, e, p, s, x" << endl;
        }
    } while (op != 'x');

    return 0;
}
/*
Operation: V b c V a f V b a V c f V b f V a c V c d V f e V d e p                                             
Edge inserted between b and c.
Operation: Edge inserted between a and f.
Operation: Edge inserted between b and a.
Operation: Edge inserted between c and f.
Operation: Edge inserted between b and f.
Operation: Edge inserted between a and c.
Operation: Edge inserted between c and d.
Operation: Edge inserted between f and e.
Operation: Edge inserted between d and e.
Operation: 
===== GRAPH =====
a -> f, b, c
b -> c, a, f
c -> b, f, a, d
d -> c, e
e -> f, d
f -> a, c, b, e
Vertices: 6
Edges: 9
Operation: s 4

Finding clique of size 4...
Clique found!
Clique: { a, b, c, f }
*/