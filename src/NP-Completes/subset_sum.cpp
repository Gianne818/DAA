#include <iostream>
using namespace std;

// Function to determine if there is a subset
// whose sum is equal to target
bool subsetSum(int arr[], int n, int target)
{
    // DP table
    // dp[i][j] means:
    // Can we form sum j using the first i elements?
    bool dp[100][1000];

    // Base Case 1:
    // Sum 0 is always possible
    // by choosing no elements
    for(int i = 0; i <= n; i++)
    {
        dp[i][0] = true;
    }

    // Base Case 2:
    // If there are no elements,
    // positive sums cannot be formed
    for(int j = 1; j <= target; j++)
    {
        dp[0][j] = false;
    }

    // Fill the DP table
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= target; j++)
        {
            // Current element
            int current = arr[i - 1];

            // If current element is bigger than the sum,
            // we cannot include it
            if(current > j)
            {
                // Copy answer from previous row
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                // Two choices:
                //
                // 1. Exclude current element
                //    dp[i - 1][j]
                //
                // 2. Include current element
                //    dp[i - 1][j - current]
                //
                // If either is true,
                // then sum j is possible
                dp[i][j] =
                    dp[i - 1][j] ||
                    dp[i - 1][j - current];
            }
        }
    }

    // Final answer:
    // Can we form target using all n elements?
    return dp[n][target];
}

int main()
{
    // Given array
    int arr[] = {3, 34, 4, 12, 5, 2};

    // Number of elements
    int n = 6;

    // Target sum
    int target = 9;

    // Check if subset exists
    if(subsetSum(arr, n, target))
    {
        cout << "Subset with given sum exists";
    }
    else
    {
        cout << "Subset with given sum does not exist";
    }

    return 0;
}