#include <bits/stdc++.h>
using namespace std;

/*
FROM LEETCODE
THIS IS NOT BRANCH AND BOUND SINCE IT WILL TLE AND 
MST bound is too weak to prune enough. 

This solution is Not MST

Traveling Salesman Problem but with DP
*/

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        
        // Remove words that are substrings of others
        vector<string> filtered;
        for (int i = 0; i < n; i++) {
            bool isSub = false;
            for (int j = 0; j < n; j++) {
                if (i != j && words[j].find(words[i]) != string::npos) {
                    isSub = true;
                    break;
                }
            }
            if (!isSub) filtered.push_back(words[i]);
        }
        
        n = filtered.size();
        if (n == 0) return words[0];
        words = filtered;
        
        // Compute overlaps
        vector<vector<int>> overlap(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int len = min(words[i].size(), words[j].size());
                    for (int k = len; k >= 0; k--) {
                        if (words[i].substr(words[i].size() - k) == words[j].substr(0, k)) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        
        // DP[mask][last] = {length, parent, superstring}
        vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));
        
        // Initialize
        for (int i = 0; i < n; i++) {
            dp[1 << i][i] = words[i].length();
        }
        
        // Fill DP
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int last = 0; last < n; last++) {
                if (dp[mask][last] == INT_MAX) continue;
                for (int next = 0; next < n; next++) {
                    if (mask & (1 << next)) continue;
                    int newMask = mask | (1 << next);
                    int newLen = dp[mask][last] + words[next].length() - overlap[last][next];
                    if (newLen < dp[newMask][next]) {
                        dp[newMask][next] = newLen;
                        parent[newMask][next] = last;
                    }
                }
            }
        }
        
        // Find best last node
        int fullMask = (1 << n) - 1;
        int bestLast = 0;
        int bestLen = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (dp[fullMask][i] < bestLen) {
                bestLen = dp[fullMask][i];
                bestLast = i;
            }
        }
        
        // Reconstruct path
        vector<int> path;
        int mask = fullMask;
        int last = bestLast;
        while (last != -1) {
            path.push_back(last);
            int prev = parent[mask][last];
            mask = mask & ~(1 << last);
            last = prev;
        }
        reverse(path.begin(), path.end());
        
        // Build result
        string result = words[path[0]];
        for (int i = 1; i < path.size(); i++) {
            int ov = overlap[path[i-1]][path[i]];
            result += words[path[i]].substr(ov);
        }
        
        return result;
    }
};