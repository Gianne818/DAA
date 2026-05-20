/*
Informal problem: Given a set of cities and pairwise distances, find the shortest tour that visits every city exactly once and returns to the start.

Natural C++ representation: Represent a complete weighted graph as an adjacency list with weights. City indices can be integers 0..n−1.

Backtracking / branch-and-bound idea: Build partial tours by adding one city at a time. Maintain the current tour length and a lower bound (e.g., using minimum outgoing edges). If the lower bound already exceeds the best tour found so far, prune that branch.

2_TSP-AdjacencyListWithWeights/main.cpp
*/

#include <iostream>
#include "tsp.hpp"

using namespace std;

int main() {
    int n;
    
    cout << "===== TSP SOLVER (Branch & Bound) =====" << endl;
    cout << "Problem: Find shortest tour visiting all cities exactly once." << endl;
    cout << endl;
    
    cout << "Enter number of cities: ";
    cin >> n;
    
    TSPSolver tsp(n);
    
    cout << "\nEnter distances (complete graph):" << endl;
    cout << "Format: u v weight" << endl;
    cout << "Enter -1 -1 to stop" << endl;
    cout << endl;
    
    int u, v;
    double w;
    
    while (true) {
        cin >> u >> v;
        if (u == -1 && v == -1) break;
        cin >> w;
        tsp.addEdge(u, v, w);
    }
    
    tsp.solve();
    tsp.printResult();
    
    return 0;
}

/*
Enter number of cities: 4

Enter distances (complete graph):
Format: u v weight
Enter -1 -1 to stop

0 1 10
0 2 15
0 3 20
1 2 35
1 3 25
2 3 30
-1 -1

Shortest Tour Cost: 80
Best Tour: 0 1 3 2 0
*/