#ifndef COLORING3_HPP
#define COLORING3_HPP

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

class ThreeColoringSolver {
private:
    vector<vector<int>> adj;
    set<int> existingVertices;
    int n;
    vector<int> colors;
    bool found;

private:
    int findVertexIdx(char v) {
        return tolower(v) - 'a';
    }

    bool isSafe(int v, int color, const vector<int>& currentColors) {
        for (int neighbor : adj[v]) {
            if (currentColors[neighbor] == color) {
                return false;
            }
        }
        return true;
    }

    void backtrack(int pos, vector<int>& currentColors) {
        if (found) return;
        
        if (pos == n) {
            found = true;
            colors = currentColors;
            return;
        }

        vector<int> vertices(existingVertices.begin(), existingVertices.end());
        int v = vertices[pos];

        for (int color = 0; color < 3; color++) {
            if (isSafe(v, color, currentColors)) {
                currentColors[v] = color;
                backtrack(pos + 1, currentColors);
                currentColors[v] = -1;
                if (found) return;
            }
        }
    }

public:
    ThreeColoringSolver() {
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
        
        vector<int> currentColors(n, -1);
        backtrack(0, currentColors);
        return found;
    }

    void printColoring() {
        if (!found) {
            cout << "No 3-coloring exists." << endl;
            return;
        }

        cout << "3-Coloring: { ";
        bool first = true;
        vector<int> vertices(existingVertices.begin(), existingVertices.end());
        sort(vertices.begin(), vertices.end());
        
        for (int v : vertices) {
            if (!first) cout << ", ";
            cout << char(toupper(v + 'a')) << "=";
            if (colors[v] == 0) cout << "Red";
            else if (colors[v] == 1) cout << "Green";
            else cout << "Blue";
            first = false;
        }
        cout << " }" << endl;
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
            cout << char(toupper(vertex + 'a')) << " -> ";
            if (adj[vertex].empty()) {
                cout << "(no edges)";
            } else {
                for (int i = 0; i < adj[vertex].size(); i++) {
                    cout << char(toupper(adj[vertex][i] + 'a'));
                    if (i != adj[vertex].size() - 1) cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "Vertices: " << existingVertices.size() << endl;
    }
};

#endif