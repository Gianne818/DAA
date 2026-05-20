// clique.hpp

#ifndef CLIQUE_HPP
#define CLIQUE_HPP

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class CliqueSolver {
private:
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;
    set<int> existingVertices;
    int n;
    int k;
    vector<bool> clique;
    bool found;

private:
    int findVertexIdx(char v) {
        return v - 'A';
    }

    bool isClique(const vector<bool>& currentClique) {
        vector<int> vertices;
        for (int i = 0; i < n; i++) {
            if (currentClique[i]) {
                vertices.push_back(i);
            }
        }

        for (int i = 0; i < vertices.size(); i++) {
            for (int j = i + 1; j < vertices.size(); j++) {
                int u = vertices[i];
                int v = vertices[j];
                bool edgeExists = false;
                for (int neighbor : adj[u]) {
                    if (neighbor == v) {
                        edgeExists = true;
                        break;
                    }
                }
                if (!edgeExists) {
                    return false;
                }
            }
        }
        return true;
    }

    void backtrack(int start, int cliqueSize, vector<bool>& currentClique) {
        if (found) return;
        
        if (cliqueSize == k) {
            if (isClique(currentClique)) {
                found = true;
                clique = currentClique;
            }
            return;
        }

        for (int i = start; i < n; i++) {
            if (!currentClique[i]) {
                currentClique[i] = true;
                backtrack(i + 1, cliqueSize + 1, currentClique);
                currentClique[i] = false;
                if (found) return;
            }
        }
    }

public:
    CliqueSolver() {
        n = 0;
        k = 0;
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
        edges.push_back({uIdx, vIdx});
    }

    bool solve(int targetK) {
        k = targetK;
        found = false;
        vector<bool> currentClique(n, false);
        backtrack(0, 0, currentClique);
        return found;
    }

    void printClique() {
        if (!found) {
            cout << "No clique of size " << k << " exists." << endl;
            return;
        }

        cout << "Clique: { ";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (clique[i]) {
                if (!first) cout << ", ";
                cout << char(i + 'A');
                first = false;
            }
        }
        cout << " }" << endl;
    }

    void printGraph() {
        cout << "\n===== GRAPH =====" << endl;
        if (existingVertices.empty()) {
            cout << "Empty graph." << endl;
            return;
        }

        for (int vertex : existingVertices) {
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
        cout << "Edges: " << edges.size() << endl;
    }
};

#endif