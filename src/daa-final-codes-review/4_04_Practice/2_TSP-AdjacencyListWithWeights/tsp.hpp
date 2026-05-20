#ifndef TSP_HPP
#define TSP_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class TSPSolver {
private:
    vector<vector<double>> dist;
    vector<bool> visited;
    vector<int> currentTour;
    vector<int> bestTour;
    double bestCost;
    int n;

    double lowerBound(int currentCity, int count, double currentCost) {
        double bound = currentCost;
        
        vector<bool> tempVisited = visited;
        tempVisited[currentCity] = true;
        
        for (int i = 0; i < n; i++) {
            if (!tempVisited[i]) {
                double minEdge = numeric_limits<double>::max();
                for (int j = 0; j < n; j++) {
                    if (i != j && !tempVisited[j] && dist[i][j] < minEdge) {
                        minEdge = dist[i][j];
                    }
                }
                if (minEdge != numeric_limits<double>::max()) {
                    bound += minEdge;
                }
            }
        }
        
        return bound;
    }

    void backtrack(int currentCity, int count, double currentCost) {
        if (count == n) {
            double totalCost = currentCost + dist[currentCity][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestTour = currentTour;
                bestTour.push_back(0);
            }
            return;
        }

        for (int nextCity = 0; nextCity < n; nextCity++) {
            if (!visited[nextCity] && dist[currentCity][nextCity] < numeric_limits<double>::max()) {
                double newCost = currentCost + dist[currentCity][nextCity];
                
                if (newCost >= bestCost) continue;
                
                double bound = lowerBound(nextCity, count + 1, newCost);
                if (bound >= bestCost) continue;
                
                visited[nextCity] = true;
                currentTour.push_back(nextCity);
                backtrack(nextCity, count + 1, newCost);
                visited[nextCity] = false;
                currentTour.pop_back();
            }
        }
    }

public:
    TSPSolver(int vertices) {
        n = vertices;
        dist.resize(n, vector<double>(n, numeric_limits<double>::max()));
        visited.resize(n, false);
        bestCost = numeric_limits<double>::max();
    }

    void addEdge(int u, int v, double w) {
        dist[u][v] = w;
        dist[v][u] = w;
    }

    void solve() {
        visited[0] = true;
        currentTour.push_back(0);
        backtrack(0, 1, 0);
    }

    void printResult() {
        cout << "\nShortest Tour Cost: " << bestCost << endl;
        cout << "Best Tour: ";
        for (int city : bestTour) {
            cout << city << " ";
        }
        cout << endl;
    }
};

#endif