#ifndef HAMILTONIANCYCLE_LIST_HPP
#define HAMILTONIANCYCLE_LIST_HPP

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class HamiltonianCycleSolver {
private:
    vector<vector<int>> adj;
    set<int> existingVertices;
    int n;
    vector<int> path;
    bool found;

private:
    int findVertexIdx(char v) {
        return v - 'a';
    }

    bool isSafe(int v, int pos, const vector<int>& currentPath) {
        if (find(adj[currentPath[pos - 1]].begin(), adj[currentPath[pos - 1]].end(), v) == adj[currentPath[pos - 1]].end()) {
            return false;
        }
        
        for (int i = 0; i < pos; i++) {
            if (currentPath[i] == v) {
                return false;
            }
        }
        return true;
    }

    void backtrack(int pos, vector<int>& currentPath) {
        if (found) return;
        
        if (pos == n) {
            if (find(adj[currentPath[pos - 1]].begin(), adj[currentPath[pos - 1]].end(), currentPath[0]) != adj[currentPath[pos - 1]].end()) {
                found = true;
                path = currentPath;
            }
            return;
        }

        for (int v : existingVertices) {
            if (isSafe(v, pos, currentPath)) {
                currentPath[pos] = v;
                backtrack(pos + 1, currentPath);
                currentPath[pos] = -1;
                if (found) return;
            }
        }
    }

public:
    HamiltonianCycleSolver() {
        n = 0;
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

    bool solve() {
        found = false;
        if (existingVertices.empty()) return false;
        
        vector<int> currentPath(n, -1);
        int start = *existingVertices.begin();
        currentPath[0] = start;
        backtrack(1, currentPath);
        return found;
    }

    void printCycle() {
        if (!found) {
            cout << "No Hamiltonian cycle exists." << endl;
            return;
        }

        cout << "Hamiltonian Cycle: ";
        for (int i = 0; i < path.size(); i++) {
            cout << char(path[i] + 'a');
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << " -> " << char(path[0] + 'a') << endl;
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
            cout << char(vertex + 'a') << " -> ";
            if (adj[vertex].empty()) {
                cout << "(no edges)";
            } else {
                for (int i = 0; i < adj[vertex].size(); i++) {
                    cout << char(adj[vertex][i] + 'a');
                    if (i != adj[vertex].size() - 1) cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "Vertices: " << existingVertices.size() << endl;
    }
};

#endif