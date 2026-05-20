#include <iostream>
using namespace std;

int n; // number of vertices

// Check if we can assign color c to vertex v
bool isSafe(int graph[][50], int color[], int v, int c)
{
    for(int i = 0; i < n; i++)
    {
        // If adjacent and same color → not safe
        if(graph[v][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

// Try coloring all vertices
bool solve(int graph[][50], int color[], int v, int k)
{
    // If all vertices colored
    if(v == n)
        return true;

    // Try all k colors
    for(int c = 1; c <= k; c++)
    {
        if(isSafe(graph, color, v, c))
        {
            color[v] = c;

            if(solve(graph, color, v + 1, k))
                return true;

            // backtrack
            color[v] = 0;
        }
    }

    return false;
}

int main()
{
    n = 4;
    int k = 3; // number of colors allowed

    int graph[50][50] =
    {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int color[50] = {0};

    if(solve(graph, color, 0, k))
    {
        cout << "Coloring possible\n";
        for(int i = 0; i < n; i++)
            cout << "Vertex " << i << " -> Color " << color[i] << "\n";
    }
    else
    {
        cout << "Not possible to color with " << k << " colors";
    }

    return 0;
}