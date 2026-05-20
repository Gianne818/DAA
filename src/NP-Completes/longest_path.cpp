#include <iostream>
using namespace std;

int n;

// DFS backtracking
bool solve(int graph[][50],
           int visited[],
           int current,
           int length,
           int k)
{
    // If required length reached
    if(length >= k)
        return true;

    // Try all neighbors
    for(int next = 0; next < n; next++)
    {
        // adjacent and not visited
        if(graph[current][next] == 1 &&
           visited[next] == 0)
        {
            visited[next] = 1;

            if(solve(graph,
                     visited,
                     next,
                     length + 1,
                     k))
            {
                return true;
            }

            // backtrack
            visited[next] = 0;
        }
    }

    return false;
}

int main()
{
    n = 5;

    int k = 4;

    int graph[50][50] =
    {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    bool found = false;

    // Try starting from every vertex
    for(int start = 0; start < n; start++)
    {
        int visited[50] = {0};

        visited[start] = 1;

        if(solve(graph,
                 visited,
                 start,
                 0,
                 k))
        {
            found = true;
            break;
        }
    }

    if(found)
        cout << "Path of length " << k << " exists";
    else
        cout << "No path of length " << k << " exists";

    return 0;
}