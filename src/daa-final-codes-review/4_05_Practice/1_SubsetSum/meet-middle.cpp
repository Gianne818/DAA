#include <bits/stdc++.h>
using namespace std;

// Generate all possible subset sums from a vector
vector<int> generateSubsetSums(vector<int>& arr, int start, int end) {
    int n = end - start;
    vector<int> sums;
    
    // Iterate over all subsets (2^n possibilities)
    for (int i = 0; i < (1 << n); i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum += arr[start + j];
            }
        }
        sums.push_back(sum);
    }
    return sums;
}

// Meet-in-the-Middle Subset Sum
bool isSubsetSum(vector<int>& arr, int target) {
    int n = arr.size();
    
    // Split array into two halves
    int mid = n / 2;
    
    // Generate all subset sums for both halves
    vector<int> leftSums = generateSubsetSums(arr, 0, mid);
    vector<int> rightSums = generateSubsetSums(arr, mid, n);
    
    // Sort right half sums for binary search
    sort(rightSums.begin(), rightSums.end());
    
    // Check for each left sum if (target - leftSum) exists in right
    for (int leftSum : leftSums) {
        int needed = target - leftSum;
        
        // Binary search in right sums
        if (binary_search(rightSums.begin(), rightSums.end(), needed)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    vector<int> arr = {1, 5, 3, 7, 4};
    int target = 12;
    
    if (isSubsetSum(arr, target))
        cout << "True" << endl;
    else cout << "False" << endl;
    
    return 0;
}