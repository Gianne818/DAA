#ifndef LONGESTPATH_HPP
#define LONGESTPATH_HPP

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class LongestPathSolver {
private:
    vector<vector<int>> adj;
    set<int> existingVertices;
    int n;
    int start;
    int target;
    int k;
    vector<int> longestPath;
    int maxLength;
    bool found;

private:
    int findVertexIdx(char v) {
        return v - 'A';
    }

    void backtrack(int current, int length, vector<bool>& visited, vector<int>& path) {
        if (current == target && length >= k) {
            found = true;
            if (length > maxLength) {
                maxLength = length;
                longestPath = path;
            }
            return;
        }

        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);
                
                backtrack(neighbor, length + 1, visited, path);
                
                path.pop_back();
                visited[neighbor] = false;
            }
        }
    }

public:
    LongestPathSolver() {
        n = 0;
        start = -1;
        target = -1;
        k = 0;
        maxLength = -1;
        found = false;
    }

    void insertVertex(char v) {
        int idx = findVertexIdx(v);
        existingVertices.insert(idx);
        if (idx >= n) {
            n = idx + 1;
            adj.resize(n);
        }
    }

    void insertEdge(char u, char v, int e) {
        int uIdx = findVertexIdx(u);
        int vIdx = findVertexIdx(v);
        insertVertex(u);
        insertVertex(v);

        for (int neighbor : adj[uIdx]) {
            if (neighbor == vIdx) {
                cout << "Edge already exists!" << endl;
                return;
            }
        }

        adj[uIdx].push_back(vIdx);
        adj[vIdx].push_back(uIdx);
    }

    bool solve(char u, char v, int targetK) {
        start = findVertexIdx(u);
        target = findVertexIdx(v);
        k = targetK;
        found = false;
        maxLength = -1;
        
        if (start == -1 || target == -1) return false;
        if (start == target && k <= 0) {
            found = true;
            longestPath = {start};
            return true;
        }
        
        vector<bool> visited(n, false);
        vector<int> path;
        path.push_back(start);
        visited[start] = true;
        
        backtrack(start, 0, visited, path);
        
        return found;
    }

    void printResult() {
        if (!found) {
            cout << "No simple path from "
                 << char(start + 'A') << " to "
                 << char(target + 'A') << " with length ≥ "
                 << k << " exists." << endl;
            return;
        }
        
        cout << "Path found! Length: " << maxLength << endl;
        cout << "Longest simple path: ";
        for (int i = 0; i < longestPath.size(); i++) {
            cout << char(longestPath[i] + 'A');
            if (i < longestPath.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    void printGraph() {
        cout << "\n===== GRAPH (Adjacency List) =====" << endl;
        if (existingVertices.empty()) {
            cout << "Empty graph." << endl;
            return;
        }

        vector<int> vertices(existingVertices.begin(), existingVertices.end());
        sort(vertices.begin(), vertices.end());
        
        for (int vertex : vertices) {
            cout << char(vertex + 'A') << " -> ";
            if (adj[vertex].empty()) {
                cout << "(no edges)";
            } else {
                for (int i = 0; i < adj[vertex].size(); i++) {
                    cout << char(adj[vertex][i] + 'A');
                    if (i != adj[vertex].size() - 1) cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "Vertices: " << existingVertices.size() << endl;
    }
};

#endif