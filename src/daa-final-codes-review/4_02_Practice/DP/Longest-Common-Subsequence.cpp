#include <bits/stdc++.h>
using namespace std;

class Solution {
    int lcs(string& X, string& Y, int i, int j, vector<vector<int>> &memo){
        if(i < 0 || j < 0) return 0; // base case
        if(memo[i][j] != -1) return memo[i][j];
        if(X[i] == Y[j]){
            memo[i][j] = lcs(X, Y, i - 1, j - 1, memo) + 1;
        } else {
            memo[i][j] = max( lcs(X, Y, i - 1, j, memo), 
                              lcs(X, Y, i, j - 1, memo) );
        }
        return memo[i][j];
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return lcs(text1, text2, n - 1, m - 1, memo);
    }
};

int main() {
    Solution sol;
    string text1 = "abcde", text2 = "ace";
    
    // cout << "Enter first string: ";
    // cin >> text1;
    
    // cout << "Enter second string: ";
    // cin >> text2;
    
    int result = sol.longestCommonSubsequence(text1, text2);
    cout << "Longest Common Subsequence length: " << result << endl;
    
    return 0;
}