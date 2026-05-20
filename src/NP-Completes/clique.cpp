#include <iostream>
using namespace std;

/*
    Check if a vertex is connected to all vertices in current clique
*/
bool isValid(int graph[][50], int currentClique[], int cliqueSize, int candidate)
{
    for(int i = 0; i < cliqueSize; i++)
    {
        // If any edge is missing, not valid
        if(graph[currentClique[i]][candidate] == 0)
            return false;
    }
    return true;
}

/*
    Branch and Bound recursive search

    currentClique   -> stores current clique vertices
    candidates      -> available vertices to try
    target          -> required clique size (k)
    cliqueSize      -> current size of clique
    candidateArraySize -> number of remaining candidates
*/
bool solveClique(int graph[][50],
                 int currentClique[],
                 int candidates[],
                 int target,
                 int cliqueSize,
                 int candidateSize)
{
    // If we already formed a clique of size k
    if(cliqueSize == target)
        return true;

    // Branch and Bound Pruning:
    // Even if we take all remaining candidates,
    // we still cannot reach target size
    if(cliqueSize + candidateSize < target)
        return false;

    // Try each candidate
    for(int i = 0; i < candidateSize; i++)
    {
        int v = candidates[i];

        // Check if we can add this vertex to clique
        if(isValid(graph, currentClique, cliqueSize, v))
        {
            // Include vertex in clique
            currentClique[cliqueSize] = v;

            // Build new candidate list (only those connected to v)
            int newCandidates[50];
            int newSize = 0;

            for(int j = i + 1; j < candidateSize; j++)
            {
                if(graph[v][candidates[j]] == 1)
                {
                    newCandidates[newSize++] = candidates[j];
                }
            }

            // Recurse
            if(solveClique(graph,
                           currentClique,
                           newCandidates,
                           target,
                           cliqueSize + 1,
                           newSize))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int n = 5; // number of vertices
    int k = 3; // target clique size

    /*
        Adjacency matrix (undirected graph)

        1 = edge exists
        0 = no edge
    */
    int graph[50][50] =
    {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0}
    };

    // Initial candidates: all vertices
    int candidates[50];
    for(int i = 0; i < n; i++)
    {
        candidates[i] = i;
    }

    int currentClique[50];

    // Start search
    if(solveClique(graph,
                   currentClique,
                   candidates,
                   k,
                   0,
                   n))
    {
        cout << "Clique of size " << k << " exists";
    }
    else
    {
        cout << "No clique of size " << k << " exists";
    }

    return 0;
}