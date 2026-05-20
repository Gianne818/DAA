#include <iostream>
#include <vector>

using namespace std;

// Tabulation with O(T) space (1D array)
bool tabulation1D(vector<int>& A, int T) {
    int n = A.size();
    vector<bool> dp(T + 1, false);
    dp[0] = true;  // sum 0 is always achievable
    
    for (int i = 0; i < n; i++) {
        // Iterate backwards to avoid reusing the same element multiple times
        for (int j = T; j >= A[i]; j--) {
            if (dp[j - A[i]]) {
                dp[j] = true;
            }
        }
    }
    
    return dp[T];
}

int main() {
    vector<int> A = {3, 5, 1};
    int T = 4;
    
    bool result = tabulation1D(A, T);
    
    cout << "Elements: ";
    for (int num : A) cout << num << " ";
    cout << endl;
    cout << "Target " << T << " -> " << (result ? "YES" : "NO") << endl;
    
    return 0;
}

/*
Time: O(n × T)

Space: O(T)
*/