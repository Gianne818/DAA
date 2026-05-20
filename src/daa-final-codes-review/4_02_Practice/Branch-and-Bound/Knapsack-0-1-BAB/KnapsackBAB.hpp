#include <bits/stdc++.h>
using namespace std;

class KnapsackBranchAndBound {
private:
    struct Node {
        int level;      // Current item index
        int profit;     // Current total profit
        int weight;     // Current total weight
        double bound;   // Upper bound of profit
        vector<bool> selected; // Items selected so far
        
        Node(int l, int p, int w, double b, int n) 
            : level(l), profit(p), weight(w), bound(b), selected(n, false) {}
    };
    
    int n;
    int capacity;
    vector<int> weights;
    vector<int> values;
    int bestValue;
    vector<bool> bestSelection;
    
    // Calculate upper bound using fractional knapsack (greedy)
    double calculateBound(Node& node) {
        if (node.weight >= capacity) return 0;
        
        double bound = node.profit;
        int totalWeight = node.weight;
        
        for (int i = node.level + 1; i < n && totalWeight + weights[i] <= capacity; i++) {
            totalWeight += weights[i];
            bound += values[i];
        }
        
        // Add fraction of next item if remaining capacity exists
        if (node.level + 1 < n && totalWeight < capacity) {
            int next = node.level + 1;
            double fraction = (double)(capacity - totalWeight) / weights[next];
            bound += values[next] * fraction;
        }
        
        return bound;
    }
    
public:
    KnapsackBranchAndBound(int cap, vector<int>& w, vector<int>& v) {
        capacity = cap;
        n = w.size();
        bestValue = 0;
        bestSelection.resize(n, false);
        
        // Create indices for sorting
        vector<pair<double, int>> ratio(n);
        for (int i = 0; i < n; i++) {
            ratio[i] = {(double)v[i] / w[i], i};
        }
        sort(ratio.begin(), ratio.end(), greater<pair<double, int>>());
        
        // Sort items by value/weight ratio (descending)
        for (int i = 0; i < n; i++) {
            int idx = ratio[i].second;
            weights.push_back(w[idx]);
            values.push_back(v[idx]);
        }
    }
    
    void solve() {
        // Create initial node (before any item)
        Node root(-1, 0, 0, 0, n);
        root.bound = calculateBound(root);
        
        // Priority queue ordered by bound (higher bound first)
        auto cmp = [](Node& a, Node& b) { return a.bound < b.bound; };
        priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
        
        pq.push(root);
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            // Prune if bound can't beat best
            if (current.bound <= bestValue) continue;
            
            // Move to next level
            int nextLevel = current.level + 1;
            if (nextLevel >= n) continue;
            
            // Branch 1: Take the next item
            Node take(nextLevel, 
                      current.profit + values[nextLevel],
                      current.weight + weights[nextLevel],
                      0, n);
            
            // Copy selection from parent
            take.selected = current.selected;
            take.selected[nextLevel] = true;
            
            if (take.weight <= capacity && take.profit > bestValue) {
                bestValue = take.profit;
                bestSelection = take.selected;
            }
            
            if (take.weight <= capacity) {
                take.bound = calculateBound(take);
                if (take.bound > bestValue) {
                    pq.push(take);
                }
            }
            
            // Branch 2: Skip the next item
            Node skip(nextLevel, current.profit, current.weight, 0, n);
            skip.selected = current.selected;
            skip.selected[nextLevel] = false;
            skip.bound = calculateBound(skip);
            
            if (skip.bound > bestValue) {
                pq.push(skip);
            }
        }
        
        // Restore original order for output
        vector<bool> originalOrder(bestSelection.size(), false);
        // Note: This mapping is complex; for simplicity we show sorted indices
        
        cout << "Maximum value: " << bestValue << endl;
        cout << "Selected items (by sorted index): ";
        for (int i = 0; i < n; i++) {
            if (bestSelection[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};