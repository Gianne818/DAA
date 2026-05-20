#include <bits/stdc++.h>
using namespace std;

class GraphList {
private:
    struct Edge {
        char dest;
        int edgeID;
    };
    struct Vertex {
        char name;
        vector<Edge> edges;
    };
    vector<Vertex> verticesList;
    int num_vert;
    int num_edge;

public:
    GraphList() {
        num_vert = 0;
        num_edge = 0;
    }

    int findVertexIdx(char v) {
        for (int i = 0; i < verticesList.size(); i++) {
            if (verticesList[i].name == v)
                return i;
        }
        return -1;
    }

    int numVertices() {
        return verticesList.size();
    }

    char* vertices() {
        char* arr = new char[verticesList.size()];
        for (int i = 0; i < verticesList.size(); i++) {
            arr[i] = verticesList[i].name;
        }
        return arr;
    }

    int numEdges() {
        return num_edge;
    }

    bool insertVertex(char x) {
        if (findVertexIdx(x) != -1) {
            cout << "Vertex already exists!" << endl;
            return false;
        }
        Vertex temp;
        temp.name = x;
        verticesList.push_back(temp);
        num_vert++;
        return true;
    }

    bool insertEdge(char u, char v, int id) {
        int uIdx = findVertexIdx(u);
        int vIdx = findVertexIdx(v);
        
        if (uIdx == -1 || vIdx == -1) {
            cout << "Vertex not found!" << endl;
            return false;
        }
        
        // Check if edge already exists
        for (Edge edge : verticesList[uIdx].edges) {
            if (edge.dest == v) {
                cout << "Edge already exists!" << endl;
                return false;
            }
        }
        
        Edge e1;
        e1.dest = v;
        e1.edgeID = id;
        verticesList[uIdx].edges.push_back(e1);
        
        Edge e2;
        e2.dest = u;
        e2.edgeID = id;
        verticesList[vIdx].edges.push_back(e2);
        
        num_edge++;
        return true;
    }

    // Hamiltonian Cycle - Find any cycle that visits every vertex exactly once
    bool findHamiltonianCycle(vector<char>& cycle) {
        vector<int> path;
        vector<bool> visited(num_vert, false);
        
        function<bool(int)> backtrack = [&](int pos) -> bool {
            if (pos == num_vert) {
                // Check if last vertex connects to first
                int lastIdx = path.back();
                int firstIdx = path[0];
                for (Edge edge : verticesList[lastIdx].edges) {
                    if (edge.dest == verticesList[firstIdx].name) {
                        return true;
                    }
                }
                return false;
            }
            
            for (int i = 0; i < num_vert; i++) {
                if (!visited[i]) {
                    // Check if current vertex connects to previous
                    if (pos == 0) {
                        // First vertex - always valid
                        path.push_back(i);
                        visited[i] = true;
                        if (backtrack(pos + 1)) return true;
                        visited[i] = false;
                        path.pop_back();
                    } else {
                        int prevIdx = path.back();
                        bool edgeExists = false;
                        for (Edge edge : verticesList[prevIdx].edges) {
                            if (edge.dest == verticesList[i].name) {
                                edgeExists = true;
                                break;
                            }
                        }
                        if (edgeExists) {
                            path.push_back(i);
                            visited[i] = true;
                            if (backtrack(pos + 1)) return true;
                            visited[i] = false;
                            path.pop_back();
                        }
                    }
                }
            }
            return false;
        };
        
        if (backtrack(0)) {
            cycle.clear();
            for (int idx : path) {
                cycle.push_back(verticesList[idx].name);
            }
            // Add start vertex to complete the cycle
            cycle.push_back(cycle[0]);
            return true;
        }
        return false;
    }

    void print() {
        for (Vertex vertex : verticesList) {
            cout << vertex.name << " -> ";
            for (int i = 0; i < vertex.edges.size(); i++) {
                cout << vertex.edges[i].dest;
                if (i != vertex.edges.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << "Vertices: " << num_vert << ", Edges: " << num_edge << endl;
    }
};