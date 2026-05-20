#ifndef TSP_DISTANCE_MATRIX_HPP
#define TSP_DISTANCE_MATRIX_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

class TSP {
private:
    int n;
    vector<vector<int>> dist;
    vector<int> currentTour;
    vector<int> bestTour;
    vector<bool> visited;
    int bestCost;

    int lowerBound(int currentCity, int count, int currentCost) {
        int bound = currentCost;
        
        vector<bool> tempVisited = visited;
        tempVisited[currentCity] = true;
        
        for (int i = 0; i < n; i++) {
            if (!tempVisited[i]) {
                int minEdge = numeric_limits<int>::max();
                for (int j = 0; j < n; j++) {
                    if (i != j && !tempVisited[j] && dist[i][j] < minEdge) {
                        minEdge = dist[i][j];
                    }
                }
                if (minEdge != numeric_limits<int>::max()) {
                    bound += minEdge;
                }
            }
        }
        
        return bound;
    }

    void solve(int currentCity, int count, int currentCost) {
        if (count == n) {
            int totalCost = currentCost + dist[currentCity][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestTour = currentTour;
                bestTour.push_back(0);
            }
            return;
        }

        for (int nextCity = 0; nextCity < n; nextCity++) {
            if (!visited[nextCity] && dist[currentCity][nextCity] < numeric_limits<int>::max()) {
                int newCost = currentCost + dist[currentCity][nextCity];
                
                if (newCost >= bestCost) continue;
                
                int bound = lowerBound(nextCity, count + 1, newCost);
                if (bound >= bestCost) continue;
                
                visited[nextCity] = true;
                currentTour.push_back(nextCity);
                solve(nextCity, count + 1, newCost);
                visited[nextCity] = false;
                currentTour.pop_back();
            }
        }
    }

public:
    TSP(const vector<vector<int>>& matrix) {
        dist = matrix;
        n = dist.size();
        visited.resize(n, false);
        bestCost = numeric_limits<int>::max();
    }

    void run() {
        if (n == 0) return;
        
        visited[0] = true;
        currentTour.push_back(0);
        solve(0, 1, 0);
        
        cout << "\n===== TSP RESULT =====" << endl;
        cout << "Shortest Tour Cost: " << bestCost << endl;
        cout << "Best Tour: ";
        for (int city : bestTour) {
            cout << city << " ";
        }
        cout << endl;
    }
};

#endif