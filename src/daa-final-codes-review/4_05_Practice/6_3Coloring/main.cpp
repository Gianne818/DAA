/*
Informal problem: Given a graph, decide whether you can assign one of three colors to each vertex so that no edge has the same color at both endpoints.

Natural C++ representation: Use an adjacency list plus a vector<int> of colors, where each color is encoded as 0, 1, or 2 (or −1 for “uncolored”).

Backtracking idea: Color vertices one by one, checking adjacency constraints locally. When a vertex has no available color consistent with its already-colored neighbors, backtrack. Heuristics such as coloring high-degree vertices first can significantly reduce the search tree.

For problems like Clique, Vertex Cover, and 3-Coloring, we typically use unweighted graphs:

Based on OpenLearning btw

Adjacency List

Case-insensitive - both 'A' and 'a' map to index 0.
*/

#include <iostream>
#include "coloring3.hpp"

using namespace std;

int main() {
    char op;
    char v;
    char u;
    char dest;
    int e;

    ThreeColoringSolver graph;

    cout << "===== 3-COLORING SOLVER =====" << endl;
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
    cout << "     Solve 3-coloring" << endl;
    cout << "     Example: s" << endl;
    cout << endl;
    cout << "  x" << endl;
    cout << "     Exit program" << endl;
    cout << "=============================" << endl;

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
                cout << "Solving 3-coloring..." << endl;
                if (graph.solve()) {
                    cout << "3-coloring found!" << endl;
                    graph.printColoring();
                } else {
                    cout << "No 3-coloring exists." << endl;
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
Operation: V a b V a b V a d s
Edge inserted between a and b.
Operation: Edge already exists!
Edge inserted between a and b.
Operation: Edge inserted between a and d.
Operation: 
Solving 3-coloring...
3-coloring found!
3-Coloring: { A=Red, B=Green, D=Green }
*/

/*
Operation: V a b V a c V a d V b c V b d V c d s   
Edge inserted between a and b.
Operation: Edge inserted between a and c.
Operation: Edge inserted between a and d.
Operation: Edge inserted between b and c.
Operation: Edge inserted between b and d.
Operation: Edge inserted between c and d.
Operation: 
Solving 3-coloring...
No 3-coloring exists.
*/