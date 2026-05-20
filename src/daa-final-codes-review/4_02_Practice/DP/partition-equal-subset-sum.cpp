// Top-down memoization (recursive + DP array).
// _______________________________________________

#include <bits/stdc++.h>
using namespace std;
class Solution {
    vector<vector<int>> mem;
    bool subsetSum(vector<int>& nums, int n, int pos, int sum){
        if(sum == 0) return true; // sum found
        else if(pos >= n || sum < 0){ // out of bounds
            return false;
        }
        if(mem[pos][sum] != -1){
            return mem[pos][sum];
        }
        return mem[pos][sum] = subsetSum(nums, n, pos + 1, sum - nums[pos]) ||
                                subsetSum(nums, n, pos + 1, sum);
    }
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            sum += nums[i];
        }
        if(sum % 2) return false;
        mem.clear();
        mem.resize(n + 1, vector<int>(sum/2 + 1, - 1));
        return subsetSum(nums, n, 0, sum / 2);
    }
};

/*
Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
 
Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= 100

________________________________________________



*/