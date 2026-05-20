// Given a set of numbers and a target sum, find all subsets that add up exactly to the target.
// CS244_DAA/4_02_Practice/Backtracking/SumOfSubsets/main.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include "sum-subsets.hpp"
using namespace std;

int main() {
    int n, target;
    vector<int> numbers;
    
    cout << "===== SUM OF SUBSETS SOLVER =====" << endl;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        numbers.push_back(num);
    }
    
    cout << "Enter target sum: ";
    cin >> target;
    
    SumOfSubsets solver;
    for (int num : numbers) {
        solver.insertNumber(num);
    }
    solver.setTarget(target);
    solver.printNumbers();
    
    // Find first subset
    vector<int> subset;
    if (solver.findSubset(subset)) {
        cout << "First subset found: {";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i != subset.size() - 1) cout << ", ";
        }
        cout << "}" << endl;
    } else {
        cout << "No subset sums to target." << endl;
    }
    
    // Find all subsets
    vector<vector<int>> subsets;
    solver.findAllSubsets(subsets);
    if (subsets.empty()) {
        cout << "No subsets sum to target." << endl;
    } else if (subsets.size() == 1) {
        cout << "Subset that sums to target:";
        cout << " {";
        for (int j = 0; j < subsets[0].size(); j++) {
            cout << subsets[0][j];
            if (j != subsets[0].size() - 1) cout << ", ";
        }
        cout << "}" << endl;
    } else {
        cout << "\nAll subsets that sum to target:" << endl;
        for (int i = 0; i < subsets.size(); i++) {
            cout << " {";
            for (int j = 0; j < subsets[i].size(); j++) {
                cout << subsets[i][j];
                if (j != subsets[i].size() - 1) cout << ", ";
            }
            cout << "}" << endl;
        }
    }
    
    return 0;
}