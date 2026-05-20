#include <iostream>
using namespace std;

const int N = 10;

int grid[N][N];
int n;

// Try placing ship at (r,c) horizontally or vertically
bool canPlace(int r, int c, int len, int dir)
{
    // dir = 0 → horizontal, 1 → vertical

    for(int i = 0; i < len; i++)
    {
        int nr = r + (dir == 1 ? i : 0);
        int nc = c + (dir == 0 ? i : 0);

        // Out of bounds
        if(nr >= n || nc >= n) return false;

        // Cell already occupied
        if(grid[nr][nc] != 0) return false;
    }

    return true;
}

// Place or remove ship
void setShip(int r, int c, int len, int dir, int val)
{
    for(int i = 0; i < len; i++)
    {
        int nr = r + (dir == 1 ? i : 0);
        int nc = c + (dir == 0 ? i : 0);
        grid[nr][nc] = val;
    }
}

// Backtracking
bool solve(int ships[], int idx, int shipCount)
{
    // Base case: all ships placed
    if(idx == shipCount)
        return true;

    int len = ships[idx];

    // Try every cell
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            // Try horizontal and vertical
            for(int dir = 0; dir < 2; dir++)
            {
                if(canPlace(r, c, len, dir))
                {
                    setShip(r, c, len, dir, 1);

                    if(solve(ships, idx + 1, shipCount))
                        return true;

                    // backtrack
                    setShip(r, c, len, dir, 0);
                }
            }
        }
    }

    return false;
}

int main()
{
    n = 5;

    // 0 = empty grid
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            grid[i][j] = 0;

    // Ship lengths
    int ships[] = {3, 2, 2};
    int shipCount = 3;

    if(solve(ships, 0, shipCount))
    {
        cout << "Solution found:\n";

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                cout << grid[i][j] << " ";
            cout << "\n";
        }
    }
    else
    {
        cout << "No solution";
    }

    return 0;
}