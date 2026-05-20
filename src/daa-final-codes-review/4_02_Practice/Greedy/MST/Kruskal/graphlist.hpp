#include <cstdlib>
#include <iostream>
#include "graph.hpp"
// #include "edge.hpp"
#include <queue> // add for pq
using namespace std;

class GraphList : public Graph {
    Edge** s_edges;
    int num_edge;
    char s_vertices[10];
    int num_vert;

    public:

    int getVertexIndex(char x){
        for(int i = 0; i < num_vert; i++){
            if(s_vertices[i] == x){
                return i;
            }
        }
        return -1;
    }
    
    GraphList() {
        s_edges = (Edge**)malloc(100 * sizeof(Edge*));
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        return s_vertices;
    }

    int numEdges() {
        return num_edge;
    }

    bool insertVertex(char x)  {
        if(num_vert >= 10){
            return false;
        }
        
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        if(getVertexIndex(u) == -1 && getVertexIndex(v) == -1){
            return false;
        }
        
        s_edges[num_edge++] = new Edge(x, u, v); // Becareful ani na constructor, the ordering arguments
        return true;
    }

    int* edges() {
        int* edge = new int[num_edge];
        for(int i = 0; i < num_edge; i++){
            edge[i] = s_edges[i]->getName();
        }
        return edge;
    }

    int getEdge(char u, char v)  {
        for(int i = 0;i < num_edge; i++){
            if(s_edges[i]-> getOrigin() == u && s_edges[i]-> getDestination() == v){
                return s_edges[i]->getName();
            }
        }
        return 0;
    }

    char* endVertices(int e)  {
        char* newVer = new char[2];
        for(int i =0; i < num_edge; i++){
            if(s_edges[i]->getName() == e){
            newVer[0] = s_edges[i]->getOrigin();
            newVer[1] = s_edges[i]->getDestination();
            return newVer;
            }
        }
        newVer[0] = '-';
        newVer[1] = '-';
        return newVer;
    }

    char opposite(char v, int e)  {
        int i = getVertexIndex(v);
        
        for(int i = 0; i < num_edge; i++){
            if(s_edges[i]->getName() == e){
                if(s_edges[i]->getOrigin() == v){
                    return s_edges[i]->getDestination();
                }
                if(s_edges[i]->getDestination() == v){
                    return s_edges[i]->getOrigin();
                }
            }
        }
        return '-';
    }

    int outDegree(char v)  {
        int ctr = 0;
        for(int i = 0; i < num_edge; i++){
            if(s_edges[i]->getOrigin() == v){
                ctr++;
            }
        }
        return ctr;
    }

    int inDegree(char v)  {
        int ctr = 0;
        for(int i = 0; i < num_edge; i++){
            if(s_edges[i]->getDestination() == v){
                ctr++;
            }
        }
        return ctr;
    }

    int* outgoingEdges(char v) {
        int deg = outDegree(v);
        int* edges = (int*)malloc(deg * sizeof(int));
        
        int ctr = 0;
        for(int i = 0; i < num_edge; i++){
            if(s_edges[i]->getOrigin()==v){
                edges[ctr++] = s_edges[i]->getName();
            }
        }
        return edges;
    }

    int* incomingEdges(char v) {
        int deg = inDegree(v);
        int* edges = (int*)malloc(deg * sizeof(int));
        
        int ctr = 0;
        for(int i = 0; i < num_edge; i++){
            if(s_edges[i]->getDestination() == v){
                edges[ctr++] = s_edges[i]->getName();
            }
        }
        return edges;
    }

    // Helper
    void deleteEdge(int i){
        delete s_edges[i];
        for(int j = i; j < num_edge - 1;j++){
            s_edges[j] = s_edges[j + 1];
        }
        num_edge--;
    }

    int removeVertex(char v) {
        int v_ind = getVertexIndex(v);
        if (v_ind == -1) return -1; 
        int sum = 0;
        sum += inDegree(v);
        sum += outDegree(v);
        
        for(int i = num_edge-1; i >=0; i--){
            if(s_edges[i]->getOrigin() == v || s_edges[i]->getDestination() == v){
                deleteEdge(i);
            }
        }
        
        for(int i = v_ind; i < num_vert - 1; i++){
            s_vertices[i] = s_vertices[i + 1];
        }
        num_vert--;
        return sum;
    }

    bool removeEdge(int e)  {
        for(int i = 0; i < num_edge; i++){
            if(s_edges[i]->getName() == e){
                deleteEdge(i);
                return true;
            }
        }
        return false;
    }

    /*
        1. Push all edges into a min-heap (sorted by weight).
        2. Union-Find to avoid cycles.
        3. Add edge to MST if it connects different components.
        4. Return array of MST edges (size = num_vert - 1).
    */

    Edge** kruskal() {
        if(num_vert == 0) return nullptr;
        
        // Min-heap of edges by weight
        auto cmp = [](Edge* a, Edge* b) { return a->getName() > b->getName(); };
        priority_queue<Edge*, vector<Edge*>, decltype(cmp)> pq(cmp);

            // same implementation as above...
        // priority_queue<Edge*, vector<Edge*>, 
        //     function<bool(Edge*, Edge*)>> pq([](Edge* a, Edge* b){
        //         return a->getName() > b->getName();
        //     });
        
        for(int i = 0; i < num_edge; i++) pq.push(s_edges[i]);
        
        // Union-Find
        int parent[10];
        for(int i = 0; i < num_vert; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x){
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };
        
        Edge** mst = (Edge**)malloc((num_vert - 1) * sizeof(Edge*));
        int mst_size = 0;
        
        while(!pq.empty() && mst_size < num_vert - 1){
            Edge* e = pq.top(); pq.pop();
            
            int u = getVertexIndex(e->getOrigin());
            int v = getVertexIndex(e->getDestination());
            if(u == -1 || v == -1) continue;
            
            int rootU = find(u), rootV = find(v);
            if(rootU != rootV){
                parent[rootV] = rootU;
                mst[mst_size++] = e;
            }
        }
        
        if(mst_size < num_vert - 1){
            free(mst);
            return nullptr;
        }
        return mst;
    }
    // Uses min-heap for edges
    // Implements Union-Find
    // Returns MST edges
    // Handles disconnected graphs





    // STRICTLY DO NOT MODIFY
    void print() {
        cout << "Vertices: ";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << " ";
        }
        cout << endl << "Edges: " << endl;
        for (int i = 0; i < num_edge; i++) {
            s_edges[i]->toString();
            cout << endl;
        }
    }



};