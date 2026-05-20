#include <bits/stdc++.h>
using namespace std;

/*
FROM LEETCODE
Branch and Bound
USES MST

However, TLE:
MST bound too weak/loose → many branches explored. For n=12, worst-case branch factor ~n! → TLE. Need tighter bound (e.g., DP for exact min remaining cost).
*/

class Solution {
private:
    int n;
    int best = INT_MAX;
    vector<vector<int>> dist;
    
    void computeAllPairsShortestPath(vector<vector<int>>& graph) {
        dist = vector<vector<int>>(n, vector<int>(n, 1e9));
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
            for (int j : graph[i]) {
                dist[i][j] = 1;
            }
        }
        
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    // MST lower bound for unvisited nodes (minimum edges to connect them)
    int mstLowerBound(int visitedMask) {
        vector<bool> inMST(n, false);
        vector<int> minEdge(n, INT_MAX);
        int total = 0;
        int nodesAdded = 0;
        
        // Find first unvisited node as start
        int start = -1;
        for (int i = 0; i < n; i++) {
            if (!(visitedMask & (1 << i))) {
                start = i;
                break;
            }
        }
        if (start == -1) return 0;
        
        minEdge[start] = 0;
        
        for (int count = 0; count < n; count++) {
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!(visitedMask & (1 << i))) { // Only unvisited nodes
                    if (!inMST[i] && (u == -1 || minEdge[i] < minEdge[u])) {
                        u = i;
                    }
                }
            }
            if (u == -1) break;
            
            inMST[u] = true;
            nodesAdded++;
            if (minEdge[u] != INT_MAX) {
                total += minEdge[u];
            }
            
            for (int v = 0; v < n; v++) {
                if (!(visitedMask & (1 << v)) && !inMST[v] && dist[u][v] < minEdge[v]) {
                    minEdge[v] = dist[u][v];
                }
            }
        }
        
        return total;
    }
    
    void branchAndBound(int visitedMask, int currNode, int currLen) {
        if (visitedMask == (1 << n) - 1) {
            best = min(best, currLen);
            return;
        }
        
        if (currLen >= best) return;
        
        // Lower bound: current length + MST of remaining unvisited nodes
        int remainingBound = mstLowerBound(visitedMask);
        if (currLen + remainingBound >= best) return;
        
        for (int next = 0; next < n; next++) {
            if (visitedMask & (1 << next)) continue;
            
            int newMask = visitedMask | (1 << next);
            int newLen = currLen + dist[currNode][next];
            
            branchAndBound(newMask, next, newLen);
        }
    }
    
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        n = graph.size();
        computeAllPairsShortestPath(graph);
        
        for (int start = 0; start < n; start++) {
            branchAndBound(1 << start, start, 0);
        }
        
        return best;
    }
};