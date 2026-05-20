// Hamiltonian Cycle: Find any cycle that visits every vertex exactly once. (Decision problem — exists or not?)
// TSP: Find the minimum weight cycle that visits every vertex exactly once. (Optimization problem — weighted graph, minimize cost.)
// Key difference: Hamiltonian checks existence, TSP finds cheapest (weights matter).
/*
in standard TSP, the graph is complete (every city connects to every other), so a Hamiltonian cycle always exists.
The challenge is finding the shortest one, not just any cycle.
Among all possible Hamiltonian cycles, find the one with minimum total distance.

CS244_DAA/4_02_Practice/Backtracking/HamiltonianCycle/main.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include "graphlist.hpp"
using namespace std;

int main() {
    char op, v, u, dest;
    int id;
    
    GraphList graph;
    
    cout << "===== HAMILTONIAN CYCLE SOLVER =====" << endl;
    cout << "Commands:" << endl;
    cout << "  v <vertex>        - Insert vertex (any character)" << endl;
    cout << "  e <u> <v> <id>    - Insert edge between u and v" << endl;
    cout << "  p                 - Print current graph" << endl;
    cout << "  h                 - Find Hamiltonian cycle" << endl;
    cout << "  x                 - Exit" << endl;
    cout << "====================================" << endl;
    
    do {
        cout << "Operation: ";
        cin >> op;
        switch(op) {
            case 'v':
                cin >> v;
                if(graph.insertVertex(v)) {
                    cout << "Vertex " << v << " inserted." << endl;
                }
                break;
                
            case 'e':
                cin >> u >> dest >> id;
                if(graph.insertEdge(u, dest, id)) {
                    cout << "Edge between " << u << " and " << dest << " inserted." << endl;
                }
                break;
                
            case 'p':
                graph.print();
                break;
                
            case 'h': {
                vector<char> cycle;
                if(graph.findHamiltonianCycle(cycle)) {
                    cout << "\nHamiltonian cycle found: ";
                    for(int i = 0; i < cycle.size(); i++) {
                        cout << cycle[i];
                        if(i != cycle.size() - 1) cout << " -> ";
                    }
                    cout << endl;
                } else {
                    cout << "\nNo Hamiltonian cycle exists." << endl;
                }
                break;
            }
                
            case 'x':
                cout << "Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid operation! Use v, e, p, h, or x." << endl;
        }
    } while(op != 'x');
    
    return 0;
}