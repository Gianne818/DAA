#include <cstdlib>
#include <iostream>
#include <climits>
#include "graph.hpp"
#include <bits/stdc++.h>
using namespace std;

class GraphMatrix : public Graph {
    int matrix[10][10];
    int s_vertices[100];
    int num_vert;
    int s_edges[100];
    int num_edge;
    
    int indexOf(int u) {
        for(int i = 0; i < num_vert; i++) {
            if(s_vertices[i] == u) return i;
        }
        
        return -1;
    }

    bool insertVertex(int x)  {
        s_vertices[num_vert++] = x;
        return true;
    }

    bool insertEdge(int u, int v, int x)  {
        int u_ind = 0, v_ind = 0;
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) {
                u_ind = i;
            }
            if (v == s_vertices[i]) {
                v_ind = i;
            }
        }
        if (matrix[u_ind][v_ind] != 0) {
            cout << "Not null" << endl;
            return false;
        }
        matrix[u_ind][v_ind] = x;
        matrix[v_ind][u_ind] = x;
        s_edges[num_edge] = x;
        num_edge++;
        return true;
    }

    int distance(int u, int v) {
        int start = indexOf(u);
        int target = indexOf(v);
        if (start == -1 || target == -1) return -1;

        bool visited[100] = {false};
        int dist[100];
        for (int i = 0; i < num_vert; i++) dist[i] = INT_MAX;

        dist[start] = 0;

        for (int count = 0; count < num_vert; count++) {
            // Find unvisited vertex with min dist
            int u = -1, minDist = INT_MAX;
            for (int i = 0; i < num_vert; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }
            if (u == -1 || u == target) break;
            visited[u] = true;

            // Relax neighbors
            for (int v_idx = 0; v_idx < num_vert; v_idx++) {
                if (matrix[u][v_idx] != 0 && !visited[v_idx]) {
                    int newDist = dist[u] + matrix[u][v_idx];
                    if (newDist < dist[v_idx]) {
                        dist[v_idx] = newDist;
                    }
                }
            }
        }

        return (dist[target] != INT_MAX) ? dist[target] : -1;
    }

    int dijkstra(int u, int v){
        return distance(u, v);
    }

    // int dijkstra(char u) { // if only one parameter, the origin...
    //     int farthestDist = -1;
    //     for (int i = 0; i < num_vert; i++) {
    //         int d = distance(u, s_vertices[i]);
    //         if (d != -1 && d > farthestDist) {
    //             farthestDist = d;
    //         }
    //     }
    //     return farthestDist;
    // }

    // DONT EDIT BELOW
    void print() {
        cout << "\t";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
            for (int j = 0; j < num_vert; j++) {
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                } else cout << ".";
                cout << "\t";
            }
            cout << endl;
        }
    }


};