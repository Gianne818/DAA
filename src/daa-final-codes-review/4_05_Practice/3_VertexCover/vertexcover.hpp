// vertexcover.hpp

#ifndef VERTEXCOVER_HPP
#define VERTEXCOVER_HPP

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class VertexCoverSolver {
private:
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;
    set<int> existingVertices;
    int n;
    int k;
    vector<bool> cover;
    bool found;

private:
    int findVertexIdx(char v) {
        return v - 'A';
    }

    bool allEdgesCovered(const vector<bool>& currentCover) {
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            if (!currentCover[u] && !currentCover[v]) {
                return false;
            }
        }
        return true;
    }

    pair<int, int> getUncoveredEdge(const vector<bool>& currentCover) {
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            if (!currentCover[u] && !currentCover[v]) {
                return {u, v};
            }
        }
        return {-1, -1};
    }

    void backtrack(int coverSize, vector<bool>& currentCover) {
        if (found) return;
        if (coverSize > k) return;
        if (allEdgesCovered(currentCover)) {
            found = true;
            cover = currentCover;
            return;
        }

        pair<int, int> edge = getUncoveredEdge(currentCover);
        int u = edge.first;
        int v = edge.second;

        if (!currentCover[u]) {
            currentCover[u] = true;
            backtrack(coverSize + 1, currentCover);
            currentCover[u] = false;
        }

        if (!currentCover[v]) {
            currentCover[v] = true;
            backtrack(coverSize + 1, currentCover);
            currentCover[v] = false;
        }
    }

public:
    VertexCoverSolver() {
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
        vector<bool> currentCover(n, false);
        backtrack(0, currentCover);
        return found;
    }

    void printCover() {
        if (!found) {
            cout << "No vertex cover of size " << k << " exists." << endl;
            return;
        }

        cout << "Vertex Cover: { ";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (cover[i]) {
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