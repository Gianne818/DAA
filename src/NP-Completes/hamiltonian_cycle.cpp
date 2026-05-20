#include <iostream>
using namespace std;

int n;

// Check if vertex can be added at position pos
bool isSafe(int graph[][50], int path[], int pos, int v)
{
    // Must be connected to previous vertex
    if(graph[path[pos - 1]][v] == 0)
        return false;

    // Must not already be in path
    for(int i = 0; i < pos; i++)
        if(path[i] == v)
            return false;

    return true;
}

// Backtracking function
bool solve(int graph[][50], int path[], int pos)
{
    // Base case: all vertices included
    if(pos == n)
    {
        // check if last connects to first (cycle)
        if(graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try all vertices
    for(int v = 1; v < n; v++)
    {
        if(isSafe(graph, path, pos, v))
        {
            path[pos] = v;

            if(solve(graph, path, pos + 1))
                return true;

            path[pos] = -1; // backtrack
        }
    }

    return false;
}

int main()
{
    n = 5;

    int graph[50][50] =
    {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    int path[50];

    // start from vertex 0
    for(int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;

    if(solve(graph, path, 1))
    {
        cout << "Hamiltonian Cycle exists:\n";
        for(int i = 0; i < n; i++)
            cout << path[i] << " ";
        cout << path[0]; // complete cycle
    }
    else
    {
        cout << "No Hamiltonian Cycle exists";
    }

    return 0;
}