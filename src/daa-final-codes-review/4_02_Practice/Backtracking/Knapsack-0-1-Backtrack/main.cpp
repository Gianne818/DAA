#include <iostream>
#include "Knapsack01.hpp"
using namespace std;

int main() {
    int n, capacity;
    
    cout << "Enter number of items: ";
    cin >> n;
    
    cout << "Enter knapsack capacity: ";
    cin >> capacity;
    
    vector<int> weights(n), values(n);
    
    cout << "Enter weight and value for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> weights[i] >> values[i];
    }
    
    Knapsack01 knapsack(capacity, weights, values);
    knapsack.solve();
    
    return 0;
}
