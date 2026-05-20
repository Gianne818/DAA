#include <iostream>
#include <vector>
using namespace std;

// Link: https://youtu.be/f-LcJs2b-p0?si=ctxBvNaiIJMimvQ3&t=1752
// Tabulation solution (bottom-up DP)
bool tabulation(vector<int>& A, int T) {
    int n = A.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(T + 1, false));
    
    // Base case: sum 0 is always achievable with empty subset
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    
    // Fill the table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= T; j++) {
            bool dont = dp[i - 1][j];           // skip current element
            bool take = false;
            if (j >= A[i - 1]) {
                take = dp[i - 1][j - A[i - 1]];  // take current element
            }
            dp[i][j] = take || dont;
        }
    }
    
    return dp[n][T];
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
    
    // Tabulation
    bool resultTab = tabulation(A, T);
    
    cout << "Elements: ";
    for (int num : A) cout << num << " ";
    cout << endl;
    cout << "Target " << T << " -> " << (resultTab ? "YES" : "NO") << endl;
    cout << endl;
    
    // Print all subsets
    printAllSubsets(A);
    
    // Print tabulation table (T/F per cell)
    vector<vector<bool>> dp(n + 1, vector<bool>(T + 1, false));
    for (int i = 0; i <= n; i++) dp[i][0] = true;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= T; j++) {
            bool dont = dp[i - 1][j];
            bool take = (j >= A[i - 1]) ? dp[i - 1][j - A[i - 1]] : false;
            dp[i][j] = take || dont;
        }
    }
    
    // Print tabulation table with dynamic spacing
    cout << "\nTabulation Table (i vs sum):\n";

    // Find max width needed for row labels
    int maxLabelWidth = 0;
    for (int i = 0; i <= n; i++) {
        string label;
        if (i == 0) label = "i=0";
        else label = "i=" + to_string(i) + " (" + to_string(A[i-1]) + ")";
        maxLabelWidth = max(maxLabelWidth, (int)label.length());
    }

    // Print header
    cout << string(maxLabelWidth + 2, ' ');
    for (int j = 0; j <= T; j++) {
        cout << j << "  ";
    }
    cout << endl;

    // Print rows
    for (int i = 0; i <= n; i++) {
        // Print row label
        if (i == 0) cout << "i=0";
        else cout << "i=" << i << " (" << A[i-1] << ")";
        
        // Pad to align
        string label;
        if (i == 0) label = "i=0";
        else label = "i=" + to_string(i) + " (" + to_string(A[i-1]) + ")";
        cout << string(maxLabelWidth - label.length() + 2, ' ');
        
        // Print cells
        for (int j = 0; j <= T; j++) {
            cout << (dp[i][j] ? "T  " : "F  ");
        }
        cout << endl;
    }
    
    return 0;
}