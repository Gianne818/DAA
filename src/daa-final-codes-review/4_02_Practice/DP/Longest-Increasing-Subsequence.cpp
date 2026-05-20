#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    
    vector<int> nums(n);
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // LIS using O(n²) DP
    vector<int> dp(n, 1);  // dp[i] = LIS ending at i
    int lisLength = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        lisLength = max(lisLength, dp[i]);
    }
    
    // Store into a lis
    vector<int> lis;
    int currentLen = lisLength;
    for (int i = n-1; i >= 0 && currentLen > 0; i--) {
        if (dp[i] == currentLen) {
            lis.push_back(nums[i]);
            currentLen--;
        }
    }
    reverse(lis.begin(), lis.end());

    cout << "Length of Longest Increasing Subsequence: " << lisLength << endl;
    cout << "The subsequence is: ";
    for (int i = 0; i < lis.size(); i++) {
        cout << lis[i] << " ";
    }
    cout << endl;
    
    return 0;
}
/*
P (solvable in poly time, DP, Memoization)
O(n^2)

Enter number of elements: 14
Enter 14 numbers: 4 3 11 9 7 13 5 6 1 12 2 8 0 10
Length of Longest Increasing Subsequence: 5
The subsequence is: 3 5 6 8 10 

Enter number of elements: 8
Enter 8 numbers: 4 3 11 9 7 13 5 6
Length of Longest Increasing Subsequence: 3
The subsequence is: 3 5 6

*/