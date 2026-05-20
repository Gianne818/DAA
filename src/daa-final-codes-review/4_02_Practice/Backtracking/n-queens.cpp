#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkDiagonal(int n, vector<string>& Board, int i, int j) {
        int row = i, col = j;
        // left diagonal
        while (row > -1 && col > -1) {
            if (Board[row][col] == 'Q') {
                return 0;
            }
            row--;
            col--;
        }

        row = i, col = j;
        // right diagonal
        while (row > -1 && col < n) {
            if (Board[row][col] == 'Q') {
                return 0;
            }
            row--;
            col++;
        }

        return 1;
    }

    void Ways(int row, int n, vector<string>& Board,
              vector<vector<string>>& ans, vector<bool>& column) {

        if (row == n) {
            ans.push_back(Board);
            return;
        }

        for (int j = 0; j < n; j++) {
            if (column[j] == 0 && checkDiagonal(n, Board, row, j)) {
                column[j] = 1;
                Board[row][j]='Q';
                Ways(row + 1, n, Board, ans, column);
                column[j] = 0;
                Board[row][j]='.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> Board(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Board[i].push_back('.');
            }
        }

        vector<bool> column(n, 0);
        Ways(0, n, Board, ans, column);
        return ans;
    }
};


/*
Time:  O(N!)
Space: O(N²) for board storage + O(N) for recursion stack → O(N²)


Input: n = 4
Output: 
".Q..", "...Q",
"Q...", "..Q.",
"..Q.", "Q...",
"...Q", ".Q.."



*/