// Mc Cauley Bacalla aka sigmacoy
// THIS IS A DP PROBLEM
#include <iostream>
#include <vector>
#include <algorithm> // max in the second nested for-loop
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items and weight capacity: ";
    cin >> n >> W;

    vector<int> values(n);
    vector<int> weights(n);

    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; ++i) {
        cin >> values[i] >> weights[i];
    }

    // Dynamic Programming Tabulation (Space-Optimized 1D Array)
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        // Traverse backwards to avoid using the same item multiple times
        for (int w = W; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }

    cout << "Maximum value in Knapsack = " << dp[W] << endl;

    return 0;
}
// Mc Cauley Bacalla aka sigmacoy



/*
TC: 1
Expected Output

Enter number of items and weight capacity: 4 50
Enter value and weight of each item:
60 10
100 20
120 30
50 40
Maximum value in Knapsack = 220

Sample Output 2

Enter number of items and weight capacity: 3 55
Enter value and weight of each item:
500 40
330 30
225 25
Maximum value in Knapsack = 555

Sample Output 3

Enter number of items and weight capacity: 3 60
Enter value and weight of each item:
60 10
100 20
120 30
Maximum value in Knapsack = 280

Expected Output 7

Enter number of items and weight capacity: 5 80
Enter value and weight of each item:
100 40
90 30
60 20
120 50
70 10
Maximum value in Knapsack = 260
*/