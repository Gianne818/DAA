#include <bits/stdc++.h>
using namespace std;

class Knapsack01 {
private:
    int n;
    int capacity;
    vector<int> weights;
    vector<int> values;
    int bestValue;
    vector<bool> bestSelection;
    
    // Bound function: estimate maximum possible value from remaining items
    int bound(int idx, int currWeight, int currValue) {
        if (currWeight > capacity) return 0;
        
        int bound = currValue;
        int totalWeight = currWeight;
        
        // Add items greedily by value/weight ratio
        for (int i = idx; i < n && totalWeight + weights[i] <= capacity; i++) {
            totalWeight += weights[i];
            bound += values[i];
        }
        
        // If there's remaining capacity, add fraction of next item
        if (idx < n && totalWeight < capacity) {
            bound += (capacity - totalWeight) * ((double)values[idx] / weights[idx]);
        }
        
        return bound;
    }
    
    void backtrack(int idx, int currWeight, int currValue, vector<bool>& selection) {
        // If all items considered, update best
        if (idx == n) {
            if (currValue > bestValue) {
                bestValue = currValue;
                bestSelection = selection;
            }
            return;
        }
        
        // Prune: if bound is less than best, skip
        if (bound(idx, currWeight, currValue) <= bestValue) {
            return;
        }
        
        // Option 1: Skip current item
        selection[idx] = false;
        backtrack(idx + 1, currWeight, currValue, selection);
        
        // Option 2: Take current item (if fits)
        if (currWeight + weights[idx] <= capacity) {
            selection[idx] = true;
            backtrack(idx + 1, currWeight + weights[idx], currValue + values[idx], selection);
        }
    }
    
public:
    Knapsack01(int cap, vector<int>& w, vector<int>& v) {
        capacity = cap;
        weights = w;
        values = v;
        n = weights.size();
        bestValue = 0;
        bestSelection.resize(n, false);
        
        // Sort by value/weight ratio for better bounding (optional)
        vector<pair<double, int>> ratio(n);
        for (int i = 0; i < n; i++) {
            ratio[i] = {(double)values[i] / weights[i], i};
        }
        sort(ratio.begin(), ratio.end(), greater<pair<double, int>>());
        
        vector<int> sortedW, sortedV;
        for (int i = 0; i < n; i++) {
            int idx = ratio[i].second;
            sortedW.push_back(weights[idx]);
            sortedV.push_back(values[idx]);
        }
        weights = sortedW;
        values = sortedV;
    }
    
    void solve() {
        vector<bool> selection(n, false);
        backtrack(0, 0, 0, selection);
        
        cout << "Maximum value: " << bestValue << endl;
        cout << "Selected items (indices after sorting): ";
        for (int i = 0; i < n; i++) {
            if (bestSelection[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};