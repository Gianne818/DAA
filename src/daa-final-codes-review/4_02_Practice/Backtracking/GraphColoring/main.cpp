// Assign colors to vertices so that no two adjacent vertices share the same color, using the fewest colors possible (or at most m colors).
// CS244_DAA/4_02_Practice/Backtracking/GraphColoring/main.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "graph.hpp"
using namespace std;

class GraphList : public Graph {
    struct Edge {
        char dest;
        int edgeID;
    };
    struct Vertex {
        char name;
        vector<Edge> edges;
    };
    vector<Vertex> verticesList;
    vector<int> edgeList;

public:
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
        return edgeList.size();
    }

    int* edges() {
        int* arr = new int[edgeList.size()];
        for (int i = 0; i < edgeList.size(); i++) {
            arr[i] = edgeList[i];
        }
        return arr;
    }

    int getEdge(char u, char v) {
        int uIdx = findVertexIdx(u);
        if (uIdx == -1)
            return 0;
        for (Edge e : verticesList[uIdx].edges) {
            if (e.dest == v)
                return e.edgeID;
        }
        return 0;
    }

    char* endVertices(int e) {
        char* arr = new char[2];
        for (Vertex vertex : verticesList) {
            for (Edge edge : vertex.edges) {
                if (edge.edgeID == e) {
                    arr[0] = vertex.name;
                    arr[1] = edge.dest;
                    return arr;
                }
            }
        }
        arr[0] = '-';
        arr[1] = '-';
        return arr;
    }

    char opposite(char v, int e) {
        char* ends = endVertices(e);
        if (ends[0] == '-')
            return '-';
        if (ends[0] == v)
            return ends[1];
        if (ends[1] == v)
            return ends[0];
        return '-';
    }

    int outDegree(char v) {
        int idx = findVertexIdx(v);
        if (idx == -1)
            return 0;
        return verticesList[idx].edges.size();
    }

    int inDegree(char v) {
        int count = 0;
        for (Vertex vertex : verticesList) {
            for (Edge edge : vertex.edges) {
                if (edge.dest == v)
                    count++;
            }
        }
        return count;
    }

    int* outgoingEdges(char v) {
        int idx = findVertexIdx(v);
        if (idx == -1)
            return NULL;
        int size = verticesList[idx].edges.size();
        int* arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = verticesList[idx].edges[i].edgeID;
        }
        return arr;
    }

    int* incomingEdges(char v) {
        int count = inDegree(v);
        int* arr = new int[count];
        int idx = 0;
        for (Vertex vertex : verticesList) {
            for (Edge edge : vertex.edges) {
                if (edge.dest == v) {
                    arr[idx++] = edge.edgeID;
                }
            }
        }
        return arr;
    }

    bool insertVertex(char x) {
        if (findVertexIdx(x) != -1) {
            cout << "Vertex already exists!" << endl;
            return false;
        }
        Vertex temp;
        temp.name = x;
        verticesList.push_back(temp);
        return true;
    }

    bool insertEdge(char u, char v, int x) {
        int uIdx = findVertexIdx(u);
        int vIdx = findVertexIdx(v);
        if (uIdx == -1 || vIdx == -1) {
            cout << "Vertex not found!" << endl;
            return false;
        }
        if (getEdge(u, v) != 0) {
            cout << "Edge already exists!" << endl;
            return false;
        }

        Edge temp;
        temp.dest = v;
        temp.edgeID = x;
        verticesList[uIdx].edges.push_back(temp);
        
        Edge temp2;
        temp2.dest = u;
        temp2.edgeID = x;
        verticesList[vIdx].edges.push_back(temp2);
        
        edgeList.push_back(x);
        return true;
    }

    int removeVertex(char v) {
        int idx = findVertexIdx(v);
        if (idx == -1)
            return 0;
        int removed = 0;
        removed += verticesList[idx].edges.size();
        for (Vertex& vertex : verticesList) {
            for (int i = 0; i < vertex.edges.size(); i++) {
                if (vertex.edges[i].dest == v) {
                    vertex.edges.erase(vertex.edges.begin() + i);
                    removed++;
                    i--;
                }
            }
        }
        verticesList.erase(verticesList.begin() + idx);
        return removed;
    }

    bool removeEdge(int e) {
        for (Vertex& vertex : verticesList) {
            for (int i = 0; i < vertex.edges.size(); i++) {
                if (vertex.edges[i].edgeID == e) {
                    vertex.edges.erase(vertex.edges.begin() + i);
                    i--;
                }
            }
        }
        for (int i = 0; i < edgeList.size(); i++) {
            if (edgeList[i] == e) {
                edgeList.erase(edgeList.begin() + i);
                return true;
            }
        }
        return false;
    }

    // Graph Coloring Implementation
    bool graphColoring(int m, map<char, int>& colorMap) {
        vector<int> colors(verticesList.size(), -1);
        
        auto isSafe = [&](int vertex, int color) -> bool {
            for (Edge edge : verticesList[vertex].edges) {
                int neighborIdx = findVertexIdx(edge.dest);
                if (colors[neighborIdx] == color) {
                    return false;
                }
            }
            return true;
        };
        
        function<bool(int)> backtrack = [&](int vertexIdx) -> bool {
            if (vertexIdx == verticesList.size()) {
                return true;
            }
            
            for (int color = 0; color < m; color++) {
                if (isSafe(vertexIdx, color)) {
                    colors[vertexIdx] = color;
                    if (backtrack(vertexIdx + 1)) {
                        return true;
                    }
                    colors[vertexIdx] = -1;
                }
            }
            return false;
        };
        
        if (backtrack(0)) {
            for (int i = 0; i < verticesList.size(); i++) {
                colorMap[verticesList[i].name] = colors[i];
            }
            return true;
        }
        return false;
    }
    
    // Find minimum colors needed
    int findMinColors() {
        for (int m = 1; m <= verticesList.size(); m++) {
            map<char, int> colorMap;
            if (graphColoring(m, colorMap)) {
                return m;
            }
        }
        return verticesList.size();
    }

    void print() {
        for (Vertex vertex : verticesList) {
            cout << vertex.name << " -> ";
            for (int i = 0; i < vertex.edges.size(); i++) {
                cout << "(" << vertex.edges[i].dest << ", " << vertex.edges[i].edgeID << ")";
                if (i != vertex.edges.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
    
    void printColoring(map<char, int>& colorMap) {
        cout << "\nGraph Coloring Solution:" << endl;
        for (auto& pair : colorMap) {
            cout << "Vertex " << pair.first << " -> Color " << pair.second;
            switch(pair.second) {
                case 0: cout << " (Red)"; break;
                case 1: cout << " (Green)"; break;
                case 2: cout << " (Blue)"; break;
                case 3: cout << " (Yellow)"; break;
                case 4: cout << " (Purple)"; break;
                default: cout << " (Color " << pair.second << ")";
            }
            cout << endl;
        }
    }
};

int main() {
    char op, v, u, dest;
    int e, m;
    
    GraphList graph;
    
    cout << "===== GRAPH COLORING SOLVER =====" << endl;
    cout << "Commands:" << endl;
    cout << "  v <vertex>        - Insert vertex (any character)" << endl;
    cout << "  e <u> <v> <id>    - Insert edge between u and v" << endl;
    cout << "  p                 - Print current graph" << endl;
    cout << "  c <m>             - Color graph with at most m colors" << endl;
    cout << "  m                 - Find minimum colors needed" << endl;
    cout << "  x                 - Exit" << endl;
    cout << "================================" << endl;
    
    do {
        cout << "Operation: ";
        cin >> op;
        switch(op) {
            case 'v':
                cin >> v;
                if(graph.insertVertex(v)) {
                    cout << "Vertex " << v << " inserted." << endl;
                }
                break;
                
            case 'e':
                cin >> u >> dest >> e;
                if(graph.insertEdge(u, dest, e)) {
                    cout << "Edge between " << u << " and " << dest << " inserted." << endl;
                }
                break;
                
            case 'p':
                graph.print();
                break;
                
            case 'c': {
                cin >> m;
                map<char, int> colorMap;
                if(graph.graphColoring(m, colorMap)) {
                    cout << "\nSuccess! Graph colored with " << m << " colors." << endl;
                    graph.printColoring(colorMap);
                } else {
                    cout << "\nFailed! Cannot color graph with " << m << " colors." << endl;
                }
                break;
            }
                
            case 'm': {
                int minColors = graph.findMinColors();
                cout << "\nMinimum colors needed: " << minColors << endl;
                map<char, int> colorMap;
                if(graph.graphColoring(minColors, colorMap)) {
                    graph.printColoring(colorMap);
                }
                break;
            }
                
            case 'x':
                cout << "Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid operation! Use v, e, p, c, m, or x." << endl;
        }
    } while(op != 'x');
    
    return 0;
}