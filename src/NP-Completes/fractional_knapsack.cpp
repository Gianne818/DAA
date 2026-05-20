#include <iostream>
using namespace std;

int main()
{
    int n = 3;

    int weight[] = {10, 20, 30};
    int profit[] = {60, 100, 120};

    int capacity = 50;

    // ratio array
    double ratio[50];

    // compute profit/weight ratio
    for(int i = 0; i < n; i++)
    {
        ratio[i] = (double)profit[i] / weight[i];
    }

    // sort by ratio descending
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(ratio[j] > ratio[i])
            {
                swap(ratio[i], ratio[j]);
                swap(weight[i], weight[j]);
                swap(profit[i], profit[j]);
            }
        }
    }

    double totalProfit = 0;

    // take items greedily
    for(int i = 0; i < n; i++)
    {
        // take full item
        if(weight[i] <= capacity)
        {
            capacity -= weight[i];
            totalProfit += profit[i];
        }
        else
        {
            // take fraction
            totalProfit += ratio[i] * capacity;
            capacity = 0;
            break;
        }
    }

    cout << "Maximum profit = " << totalProfit;

    return 0;
}