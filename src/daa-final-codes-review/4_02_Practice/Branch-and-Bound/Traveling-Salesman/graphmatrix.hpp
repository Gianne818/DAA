#include <cstdlib>
#include <iostream>
#include <climits>
#include "graph.hpp"
#include <bits/stdc++.h>
using namespace std;

// TSP Node for Branch and Bound
struct TSPNode {
    int level;           // Number of vertices visited
    int currVertex;      // Current vertex position
    int cost;            // Current path cost
    int bound;           // Lower bound
    vector<bool> visited;
    vector<int> path;
    
    TSPNode(int l, int v, int c, int b, int n) 
        : level(l), currVertex(v), cost(c), bound(b), visited(n, false) {}
};

class GraphMatrix : public Graph {
    int matrix[10][10];
    int s_vertices[100];
    int num_vert;
    int s_edges[100];
    int num_edge;
    
    int indexOf(int u) {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == u) return i;
        }
        
        return -1;
    }

    bool insertVertex(int x)  {
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(int u, int v, int x)  {
        int u_ind = 0, v_ind = 0;
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) {
                u_ind = i;
            }
            if (v == s_vertices[i]) {
                v_ind = i;
            }
        }
        if (matrix[u_ind][v_ind] != 0) {
            cout << "Not null" << endl;
            return false;
        }
        matrix[u_ind][v_ind] = x;
        matrix[v_ind][u_ind] = x;
        s_edges[num_edge] = x;
        num_edge++;
        return true;
    }

    int distance(int u, int v) {
        int start = indexOf(u);
        int target = indexOf(v);
        if (start == -1 || target == -1) return -1;

        bool visited[100] = {false};
        int dist[100];
        for (int i = 0; i < num_vert; i++) dist[i] = INT_MAX;

        dist[start] = 0;

        for (int count = 0; count < num_vert; count++) {
            // Find unvisited vertex with min dist
            int u = -1, minDist = INT_MAX;
            for (int i = 0; i < num_vert; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            if (u == -1 || u == target) break;
            visited[u] = true;

            // Relax neighbors
            for (int v_idx = 0; v_idx < num_vert; v_idx++) {
                if (matrix[u][v_idx] != 0 && !visited[v_idx]) {
                    int newDist = dist[u] + matrix[u][v_idx];
                    if (newDist < dist[v_idx]) {
                        dist[v_idx] = newDist;
                    }
                }
            }
        }

        return (dist[target] != INT_MAX) ? dist[target] : -1;
    }

    // Calculate lower bound for TSP using MST of unvisited vertices
    int tspLowerBound(const TSPNode& node, int n, int matrix[10][10]) {
        if (node.level == n - 1) {
            // If only one vertex left, add edge to it and back to start
            return node.cost;
        }
        
        // Build MST for unvisited vertices + current vertex
        vector<bool> inMST(n, false);
        vector<int> minEdge(n, INT_MAX);
        int total = 0;
        
        // Start from current vertex
        minEdge[node.currVertex] = 0;
        
        for (int count = 0; count < n - node.level; count++) {
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!node.visited[i] && !inMST[i] && (u == -1 || minEdge[i] < minEdge[u])) {
                    u = i;
                }
            }
            if (u == -1) break;
            
            inMST[u] = true;
            if (minEdge[u] != INT_MAX) {
                total += minEdge[u];
            }
            
            for (int v = 0; v < n; v++) {
                if (!node.visited[v] && !inMST[v] && matrix[u][v] != 0 && matrix[u][v] < minEdge[v]) {
                    minEdge[v] = matrix[u][v];
                }
            }
        }
        
        // Add minimum edges from start to visited set (not needed for bound)
        return node.cost + total;
    }

    int tspBranchAndBound(int start) {
        if (num_vert == 0) {
            cout << "No vertices in graph" << endl;
            return -1;
        }
        
        int bestCost = INT_MAX;
        vector<int> bestPath;
        
        // Initial node
        TSPNode root(0, start, 0, 0, num_vert);
        root.visited[start] = true;
        root.path.push_back(start);
        root.bound = tspLowerBound(root, num_vert, matrix);
        
        // Priority queue (min-heap by bound)
        auto cmp = [](const TSPNode& a, const TSPNode& b) { return a.bound > b.bound; };
        priority_queue<TSPNode, vector<TSPNode>, decltype(cmp)> pq(cmp);
        
        pq.push(root);
        
        while (!pq.empty()) {
            TSPNode current = pq.top();
            pq.pop();
            
            if (current.bound >= bestCost) continue;
            
            if (current.level == num_vert - 1) {
                int lastToStart = matrix[current.currVertex][start];
                if (lastToStart != 0) {
                    int totalCost = current.cost + lastToStart;
                    if (totalCost < bestCost) {
                        bestCost = totalCost;
                        bestPath = current.path;
                        bestPath.push_back(start);
                    }
                }
                continue;
            }
            
            for (int next = 0; next < num_vert; next++) {
                if (!current.visited[next] && matrix[current.currVertex][next] != 0) {
                    TSPNode child(current.level + 1, next, 
                                current.cost + matrix[current.currVertex][next],
                                0, num_vert);
                    child.visited = current.visited;
                    child.visited[next] = true;
                    child.path = current.path;
                    child.path.push_back(next);
                    
                    child.bound = tspLowerBound(child, num_vert, matrix);
                    
                    if (child.bound < bestCost) {
                        pq.push(child);
                    }
                }
            }
        }
        
        if (bestCost == INT_MAX) {
            cout << "No Hamiltonian cycle found" << endl;
            return -1;
        } else {
            cout << "Path: ";
            for (int v : bestPath) {
                cout << v << " ";
            }
            cout << endl;
            cout << "Total cost: " << bestCost << endl;
            return bestCost;
        }
    }

    void solveTSP() {
        for (int i = 0; i < num_vert; i++) {
            cout << "Starting from vertex " << s_vertices[i] << ": ";
            tspBranchAndBound(i);
        }
    }

    void solveTSP(int start) {
        tspBranchAndBound(start);
    }


    // DONT EDIT BELOW
    void print() {
        cout << "\t";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
            for (int j = 0; j < num_vert; j++) {
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                } else cout << ".";
                cout << "\t";
            }
            cout << endl;
        }
    }


};