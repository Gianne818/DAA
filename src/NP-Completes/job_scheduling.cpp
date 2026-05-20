#include <iostream>
using namespace std;

int main()
{
    int n = 5;

    // jobs: (id, deadline, profit)
    int id[] = {1, 2, 3, 4, 5};
    int dead[] = {2, 1, 2, 1, 3};
    int profit[] = {100, 19, 27, 25, 15};

    // Step 1: sort by profit (simple selection sort)
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(profit[j] > profit[i])
            {
                swap(profit[i], profit[j]);
                swap(dead[i], dead[j]);
                swap(id[i], id[j]);
            }
        }
    }

    // Step 2: find max deadline
    int maxDead = dead[0];
    for(int i = 1; i < n; i++)
        if(dead[i] > maxDead)
            maxDead = dead[i];

    // Step 3: time slots
    int slot[100];
    for(int i = 0; i < maxDead; i++)
        slot[i] = -1;

    int totalProfit = 0;

    // Step 4: schedule jobs
    for(int i = 0; i < n; i++)
    {
        // try latest available slot before deadline
        for(int j = dead[i] - 1; j >= 0; j--)
        {
            if(slot[j] == -1)
            {
                slot[j] = id[i];
                totalProfit += profit[i];
                break;
            }
        }
    }

    // Output
    cout << "Scheduled jobs: ";
    for(int i = 0; i < maxDead; i++)
    {
        if(slot[i] != -1)
            cout << slot[i] << " ";
    }

    cout << "\nTotal profit: " << totalProfit;

    return 0;
}