#include <iostream>
#include <algorithm>
using namespace std;

int knapsack(int s, int weightCap, int* items, int* weights){
    int table[s+1][weightCap+1];
    
    for(int i = 0; i<=s; i++){
        for(int j = 0; j<=weightCap; j++){
            if(i == 0 || j == 0) table[i][j] = 0;
            else if (weights[i-1] <= j){
                //if weight of item is less than or equal to current weight j
                // then choose greater value from current item + value of prev row and its weight in table,
                // vs the value of prev row with its current weight j
                table[i][j] = max(items[i-1] + table[i-1][j - weights[i-1]], table[i-1][j]);
            } else {
                table[i][j] = table[i-1][j];
            }
        }
    }
    return table[s][weightCap];
}

int main(){
    cout << "Enter number of items and weight capacity: ";
    int s, weightCap;
    cin >> s >> weightCap;
    
    int* items = new int[s];
    int* weights = new int[s];
    cout << "Enter value and weight of each item:" << endl;
    for(int i = 0; i<s; i++){
        cin >> items[i] >> weights[i];
    }
    
    int res = knapsack(s, weightCap, items, weights);
    cout << "Maximum value in Knapsack = " << res;
}