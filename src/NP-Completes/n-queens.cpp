#include <iostream>
using namespace std;

int n;

// Check if queen can be placed at (row, col)
bool isSafe(int board[][50], int row, int col)
{
    // Check column
    for(int i = 0; i < row; i++)
    {
        if(board[i][col] == 1)
            return false;
    }

    // Check upper-left diagonal
    for(int i = row - 1, j = col - 1;
        i >= 0 && j >= 0;
        i--, j--)
    {
        if(board[i][j] == 1)
            return false;
    }

    // Check upper-right diagonal
    for(int i = row - 1, j = col + 1;
        i >= 0 && j < n;
        i--, j++)
    {
        if(board[i][j] == 1)
            return false;
    }

    return true;
}

// Backtracking
bool solve(int board[][50], int row)
{
    // All queens placed
    if(row == n)
        return true;

    // Try every column
    for(int col = 0; col < n; col++)
    {
        if(isSafe(board, row, col))
        {
            // Place queen
            board[row][col] = 1;

            if(solve(board, row + 1))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

int main()
{
    n = 4;

    int board[50][50] = {0};

    if(solve(board, 0))
    {
        cout << "Solution found:\n";

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }
    else
    {
        cout << "No solution";
    }

    return 0;
}