/*
Informal problem: Given a set of cities and pairwise distances, find the shortest tour that visits every city exactly once and returns to the start.

Natural C++ representation: Represent a complete weighted graph as a 2D distance matrix (vector<vector<double>>). City indices can be integers 0..n−1.

Backtracking / branch-and-bound idea: Build partial tours by adding one city at a time. Maintain the current tour length and a lower bound (e.g., using minimum outgoing edges). If the lower bound already exceeds the best tour found so far, prune that branch.

Graph-based problems (TSP, Clique, Vertex Cover, 3-Coloring):
Adjacency list: vector<vector<int>> for neighbors
Optional: vector<pair<int,int>> for edges

Distance matrix: vector<vector<int>> or vector<vector<double>>
Tour representation: vector<int> for city order

2_TSP-DistanceMatrix/main.cpp
*/

#include <iostream>
#include <vector>
#include "tsp.hpp"

using namespace std;

int main() {
    cout << "===== TSP SOLVER (Distance Matrix) =====" << endl;
    cout << "Problem: Find shortest tour visiting all cities exactly once." << endl;
    cout << endl;
    
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    
    vector<vector<int>> matrix(n, vector<int>(n));
    
    cout << "\nEnter distance matrix (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    
    TSP tsp(matrix);
    tsp.run();
    
    return 0;
}

/*
===== TSP SOLVER (Distance Matrix) =====
Problem: Find shortest tour visiting all cities exactly once.

Enter number of cities: 4

Enter distance matrix (4x4):
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

===== TSP RESULT =====
Shortest Tour Cost: 80
Best Tour: 0 1 3 2 0
*/