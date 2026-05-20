// graphcoloring.hpp

#ifndef GRAPHCOLORING_HPP
#define GRAPHCOLORING_HPP

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

class GraphColoringSolver {
private:
    vector<vector<int>> adj;
    set<int> existingVertices;
    int n;
    int chromaticNumber;
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

    void backtrack(int pos, int m, vector<int>& currentColors) {
        if (found) return;
        
        if (pos == n) {
            found = true;
            colors = currentColors;
            chromaticNumber = m;
            return;
        }

        vector<int> vertices(existingVertices.begin(), existingVertices.end());
        int v = vertices[pos];

        for (int color = 0; color < m; color++) {
            if (isSafe(v, color, currentColors)) {
                currentColors[v] = color;
                backtrack(pos + 1, m, currentColors);
                currentColors[v] = -1;
                if (found) return;
            }
        }
    }

public:
    GraphColoringSolver() {
        n = 0;
        chromaticNumber = 0;
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

    int findMinColors() {
        if (existingVertices.empty()) return 0;
        
        for (int m = 1; m <= n; m++) {
            found = false;
            vector<int> currentColors(n, -1);
            backtrack(0, m, currentColors);
            if (found) {
                return m;
            }
        }
        return n;
    }

    void printResult() {
        int minColors = findMinColors();
        cout << "\n===== RESULT =====" << endl;
        cout << "Minimum colors needed: " << minColors << endl;
        
        found = false;
        vector<int> currentColors(n, -1);
        backtrack(0, minColors, currentColors);
        
        cout << "Optimal coloring: { ";
        bool first = true;
        vector<int> vertices(existingVertices.begin(), existingVertices.end());
        sort(vertices.begin(), vertices.end());
        
        for (int v : vertices) {
            if (!first) cout << ", ";
            cout << char(toupper(v + 'a')) << "=";
            if (colors[v] == 0) cout << "Red";
            else if (colors[v] == 1) cout << "Green";
            else if (colors[v] == 2) cout << "Blue";
            else cout << "Color" << colors[v];
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