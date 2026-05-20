#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkDiagonal(int n, vector<string>& Board, int i, int j) {
        int row = i, col = j;
        // left diagonal
        while (row > -1 && col > -1) {
            if (Board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        row = i, col = j;
        // right diagonal
        while (row > -1 && col < n) {
            if (Board[row][col] == 'Q') return false;
            row--;
            col++;
        }

        return true;
    }

    void Ways(int row, int n, vector<string>& Board, int& count, vector<bool>& column) {
        if (row == n) {
            count++;
            return;
        }

        for (int j = 0; j < n; j++) {
            if (column[j] == 0 && checkDiagonal(n, Board, row, j)) {
                column[j] = 1;
                Board[row][j] = 'Q';
                Ways(row + 1, n, Board, count, column);
                column[j] = 0;
                Board[row][j] = '.';
            }
        }
    }

    int totalNQueens(int n) {
        int count = 0;
        vector<string> Board(n, string(n, '.'));
        vector<bool> column(n, false);
        Ways(0, n, Board, count, column);
        return count;
    }
};