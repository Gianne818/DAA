/*

Input: Graph G, set of vertices u,v, integer k.
Question: Is there a simple path from u to v with length ≥ k?

Graph
- Adjacency List Representation

Undirected

*/

#include <iostream>
#include "longestpath.hpp"

using namespace std;

int main() {
    char op;
    char v;
    char u;
    char dest;
    char start, target;
    int e;
    int k;

    LongestPathSolver graph;

    cout << "===== LONGEST PATH SOLVER =====" << endl;
    cout << "Problem: Find simple path from u to v with length ≥ k" << endl;
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
    cout << "  V <u> <v> <edge>" << endl;
    cout << "     Example: V A B 5" << endl;
    cout << endl;
    cout << "  p" << endl;
    cout << "     Print graph" << endl;
    cout << endl;
    cout << "  s <start> <target> <k>" << endl;
    cout << "     Find longest path from start to target with length ≥ k" << endl;
    cout << "     Example: s A B 3" << endl;
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
                cin >> u >> v >> e;
                graph.insertVertex(u);
                graph.insertVertex(v);
                graph.insertEdge(u, v, e);
                cout << "Both Edges inserted between " << u << " and " << v << "." << endl;
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
                cin >> start >> target >> k;
                cout << "Finding simple path from " << start 
                     << " to " << target << " with length ≥ " << k << "..." << endl;
                
                if (graph.solve(start, target, k)) {
                    cout << "Path found!" << endl;
                    graph.printResult();
                } else {
                    cout << "No path exists." << endl;
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

// V a b 5 V b c 5 V a d 5 V d e 5 V e c 5 
/*
Operation: V a b 5 V b c 5 V a d 5 V d e 5 V e c 5 
Both Edges inserted between a and b.
Operation: Both Edges inserted between b and c.
Operation: Both Edges inserted between a and d.
Operation: Both Edges inserted between d and e.
Operation: Both Edges inserted between e and c.
Operation: s a c 2

Finding simple path from a to c with length ≥ 2...
Path found!
Path found! Length: 3
Longest simple path: a -> d -> e -> c
Operation: s a c 3

Finding simple path from a to c with length ≥ 3...
Path found!
Path found! Length: 3
Longest simple path: a -> d -> e -> c
Operation: s a c 4

Finding simple path from a to c with length ≥ 4...
No path exists.
*/