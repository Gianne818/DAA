#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Memoization solution
bool subsetSumMemo(vector<int>& A, int i, int rem, vector<vector<int>>& memo) {
    // Base cases
    if (rem == 0) return true;
    if (rem < 0 || i == A.size()) return false;
    
    // Check memo
    if (memo[i][rem] != -1) return memo[i][rem];
    
    // Recursive cases: skip OR take
    bool skip = subsetSumMemo(A, i + 1, rem, memo);
    bool take = subsetSumMemo(A, i + 1, rem - A[i], memo);
    
    // Store and return
    return memo[i][rem] = skip || take;
}

void printAllSubsets(vector<int>& A) {
    int n = A.size();
    int total = 1 << n;
    
    for (int mask = 0; mask < total; mask++) {
        cout << "{";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (!first) cout << ", ";
                cout << A[i];
                first = false;
            }
        }
        cout << "}" << endl;
    }
}

int main() {
    vector<int> A = {3, 5, 1};
    int T = 4;
    int n = A.size();
    
    // Memo table: -1 = uncomputed, 0 = false, 1 = true
    vector<vector<int>> memo(n + 1, vector<int>(T + 1, -1));
    
    bool result = subsetSumMemo(A, 0, T, memo);
    
    cout << "\n\nElements: ";
    for(int num : A){
        cout << num << " ";
    }
    cout << endl;
    cout << "Target " << T << " -> " << (result ? "YES" : "NO") << endl;
    cout << endl;

    // Print all possible subset and \n
    printAllSubsets(A);

    // Print memo table (optional)
    cout << "\nMemoization Table (i vs remaining sum):\n";
    for (int i = 0; i < n; i++) {
        cout << "i=" << i << ": ";
        for (int rem = 0; rem <= T; rem++) {
            if (memo[i][rem] == 1) cout << "✅ "; // 1
            else if (memo[i][rem] == 0) cout << "❌ "; // 0
            else cout << "?  "; // -1
        }
        cout << endl;
    }
    
    return 0;
}
/*
Do note that: 9 columns of '?'

? means that state (i, rem) was never visited during recursion.
Because recursion stops when rem == 0 (found solution) or rem < 0 (overshot) or i == n (no elements left). Unvisited states are never needed.

dp(0,8) = ✅ → Solution exists starting at index 0 (element 3)

dp(1, 5) means: starting at index 1 with remaining sum 5 → can we reach 0?
That means we took the 3 first (8–3=5), then try {5,1} → succeeds (take 5) → ✅
But eventually fails at the last element.



*/