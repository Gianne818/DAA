#ifndef CLIQUE_MATRIX_HPP
#define CLIQUE_MATRIX_HPP

#include <iostream>
#include <vector>
#include <set>
using namespace std;

class CliqueSolver {
private:
    vector<vector<bool>> adjMatrix;
    set<int> existingVertices;
    int n;
    int k;
    vector<bool> clique;
    bool found;

private:
    int findVertexIdx(char v) {
        return v - 'a';
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
                if (!adjMatrix[u][v]) {
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
            int oldN = n;
            n = idx + 1;
            adjMatrix.resize(n, vector<bool>(n, false));
            for (int i = 0; i < oldN; i++) {
                adjMatrix[i].resize(n, false);
            }
        }
    }

    void insertEdge(char u, char v, int e) {
        int uIdx = findVertexIdx(u);
        int vIdx = findVertexIdx(v);
        insertVertex(u);
        insertVertex(v);

        if (adjMatrix[uIdx][vIdx]) {
            cout << "Edge already exists!" << endl;
            return;
        }

        adjMatrix[uIdx][vIdx] = true;
        adjMatrix[vIdx][uIdx] = true;
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
                cout << char(i + 'a');
                first = false;
            }
        }
        cout << " }" << endl;
    }

    void printGraph() {
        cout << "\n===== GRAPH (Adjacency Matrix) =====" << endl;
        if (existingVertices.empty()) {
            cout << "Empty graph." << endl;
            return;
        }

        cout << "   ";
        for (int vertex : existingVertices) {
            cout << " " << char(vertex + 'a');
        }
        cout << endl;

        for (int i : existingVertices) {
            cout << " " << char(i + 'a') << " ";
            for (int j : existingVertices) {
                cout << (adjMatrix[i][j] ? "1 " : "0 ");
            }
            cout << endl;
        }
        cout << "Vertices: " << existingVertices.size() << endl;
    }
};

#endif