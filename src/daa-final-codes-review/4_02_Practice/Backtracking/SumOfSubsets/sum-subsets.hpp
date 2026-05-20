#include <bits/stdc++.h>
using namespace std;

class SumOfSubsets {
private:
    vector<int> numbers;
    int target;
    vector<int> currentSubset;
    vector<vector<int>> allSubsets;
    bool found;

    void backtrack(int start, int currentSum) {
        if (found) return;
        
        if (currentSum == target) {
            found = true;
            return;
        }
        
        if (currentSum > target) return;
        
        for (int i = start; i < numbers.size(); i++) {
            currentSubset.push_back(numbers[i]);
            backtrack(i + 1, currentSum + numbers[i]);
            if (found) return;
            currentSubset.pop_back();
        }
    }
    
    void backtrackAll(int start, int currentSum) {
        if (currentSum == target) {
            allSubsets.push_back(currentSubset);
            return;
        }
        
        if (currentSum > target) return;
        
        for (int i = start; i < numbers.size(); i++) {
            if (currentSum + numbers[i] > target) continue;
            
            currentSubset.push_back(numbers[i]);
            backtrackAll(i + 1, currentSum + numbers[i]);
            currentSubset.pop_back();
        }
    }

public:
    SumOfSubsets() {
        target = 0;
        found = false;
    }

    void insertNumber(int num) {
        numbers.push_back(num);
    }

    void setTarget(int t) {
        target = t;
    }

    bool findSubset(vector<int>& subset) {
        currentSubset.clear();
        found = false;
        backtrack(0, 0);
        
        if (found) {
            subset = currentSubset;
            return true;
        }
        return false;
    }
    
    void findAllSubsets(vector<vector<int>>& subsets) {
        currentSubset.clear();
        allSubsets.clear();
        sort(numbers.begin(), numbers.end());
        backtrackAll(0, 0);
        subsets = allSubsets;
    }
    
    void printNumbers() {
        cout << "Numbers: {";
        for (int i = 0; i < numbers.size(); i++) {
            cout << numbers[i];
            if (i != numbers.size() - 1) cout << ", ";
        }
        cout << "}" << endl;
        cout << "Target: " << target << endl;
    }
};