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

    
    
    Edge** primJarnik(char startVertex) {
        if (num_vert == 0) return nullptr;
        
        int startIdx = getVertexIndex(startVertex);
        if (startIdx == -1) return nullptr;
        
        // Track which vertices are in MST
        bool inMST[10] = {false};
        inMST[startIdx] = true;
        
        // Store MST edges
        Edge** mst = (Edge**)malloc((num_vert - 1) * sizeof(Edge*));
        int mst_size = 0;
        
        // Min-heap for edges: pair<weight, Edge*>
        auto cmp = [](pair<int, Edge*> a, pair<int, Edge*> b) {
            return a.first > b.first;
        };
        priority_queue<pair<int, Edge*>, vector<pair<int, Edge*>>, decltype(cmp)> pq(cmp);
        
        // Add all edges from start vertex to PQ
        for (int i = 0; i < num_edge; i++) {
            if (s_edges[i]->getOrigin() == startVertex) {
                pq.push({s_edges[i]->getName(), s_edges[i]});
            }
            if (s_edges[i]->getDestination() == startVertex) {
                pq.push({s_edges[i]->getName(), s_edges[i]});
            }
        }
        
        while (!pq.empty() && mst_size < num_vert - 1) {
            auto [weight, edge] = pq.top();
            pq.pop();
            
            char u = edge->getOrigin();
            char v = edge->getDestination();
            int uIdx = getVertexIndex(u);
            int vIdx = getVertexIndex(v);
            
            // Check which endpoint is not in MST
            char newVertex;
            if (inMST[uIdx] && !inMST[vIdx]) {
                newVertex = v;
                mst[mst_size++] = edge;
                inMST[vIdx] = true;
            } 
            else if (!inMST[uIdx] && inMST[vIdx]) {
                newVertex = u;
                mst[mst_size++] = edge;
                inMST[uIdx] = true;
            }
            else {
                continue; // Both already in MST or both not (skip cycle)
            }
            
            // Add all edges from new vertex to PQ
            for (int i = 0; i < num_edge; i++) {
                if (s_edges[i]->getOrigin() == newVertex) {
                    int destIdx = getVertexIndex(s_edges[i]->getDestination());
                    if (!inMST[destIdx]) {
                        pq.push({s_edges[i]->getName(), s_edges[i]});
                    }
                }
                if (s_edges[i]->getDestination() == newVertex) {
                    int origIdx = getVertexIndex(s_edges[i]->getOrigin());
                    if (!inMST[origIdx]) {
                        pq.push({s_edges[i]->getName(), s_edges[i]});
                    }
                }
            }
        }
        
        if (mst_size < num_vert - 1) {
            free(mst);
            return nullptr;
        }
        return mst;
    }





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