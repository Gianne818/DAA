#include <iostream>
#include <vector>
using namespace std;

int getMinimumOutgoingEdge(int curCity, bool* hasVisited, int n, int** matrix){
    int min = 99999;
    for(int i = 0; i<n; i++){
        if(curCity != i && (!hasVisited[i] || i == 0) && matrix[curCity][i] < min){
            min = matrix[curCity][i];
        }
    }
    
    return (min == 99999) ? 0 : min;
}

int getLowerBound(int curCost, int curCity, bool* hasVisited, int n, int** matrix){
    int bound = curCost;
    int secMin = 99999;
    bool foundUnvisited = false;
    
    for(int i = 0; i<n; i++){
        if(!hasVisited[i] && matrix[curCity][i] < secMin){
            secMin = matrix[curCity][i];
            foundUnvisited = true;
        }
    }
    
    if(!foundUnvisited){
        bound += matrix[curCity][0];   
    }
     else {
         bound+=secMin;
         for(int i = 0; i<n; i++){
             if(!hasVisited[i]){
                 bound+=getMinimumOutgoingEdge(i, hasVisited, n, matrix);
             }
         }
     }
     return bound;
}


int solveCurrent(int curCity, int countVisited, int curCost, int currMinCost, bool* hasVisited, int n, int** matrix){
    
    //base case: visited all. return to start
    if(countVisited == n){
        return curCost + matrix[curCity][0];
    }
    
    int minCost = currMinCost;
    
    for(int i = 0; i<n; i++){
        if(!hasVisited[i]){
            int newCost = curCost + matrix[curCity][i];
            int bound = getLowerBound(curCost + matrix[curCity][i], i, hasVisited, n, matrix);
            if(bound < minCost){
                hasVisited[i] = true;
                int res = solveCurrent(i, countVisited+1, curCost+matrix[curCity][i], minCost, hasVisited, n, matrix);
                if(res < minCost){
                    minCost = res;
                }
                hasVisited[i] = false;
            }
        }
    }
    
    return minCost;
}

int solveTSP(int n, int** matrix){
    
    bool hasVisited[n];
    
    
    for(int i = 0; i<n; i++){
        hasVisited[i] = false;
    }
    hasVisited[0] = true;
    
    return solveCurrent(0, 1, 0, 999999, hasVisited, n, matrix);
}

int main (){
    cout << "Enter number of cities: ";
    int n;
    cin >> n;
    
    int** matrix = (int**) calloc(n, sizeof(int*));
    for(int i = 0; i<n; i++){
        matrix[i] = (int*) calloc(n, sizeof(int));
    }
    cout << "Enter adjacency matrix:\n";
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cin >> matrix[i][j];
        }
    }
    
    cout << "Minimum cost: " << solveTSP(n, matrix);
}