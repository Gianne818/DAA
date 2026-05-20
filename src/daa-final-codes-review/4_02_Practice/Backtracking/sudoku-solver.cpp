#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool isValid(vector<vector<char>>& board, int r, int c, char val) {
        for (int i = 0; i < 9; i++) {
            if(board[r][i]== val) return false;
            if(board[i][c]== val) return false;
            int startRow = 3 * (r / 3) + i / 3, startCol = 3 * (c / 3) + i % 3;

            if(board[startRow][startCol] == val) return false;
        }
        return true;        
    }
    bool solve(vector<vector<char>>& board){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.'){
                    for(char n = '1'; n <= '9'; n++){
                        if(isValid(board, i, j, n)){
                            board[i][j] = n;
                            if(solve(board)) return true; // recursive call
                            else board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }

        return true;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};

// time -> O(9 pow n) , where n is number of empty cells
// space -> O(n^2) kay recursion stack depth call
/*

Input: board = [
["5","3",".",".","7",".",".",".","."],
["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]]

Output: [
["5","3","4","6","7","8","9","1","2"],
["6","7","2","1","9","5","3","4","8"],
["1","9","8","3","4","2","5","6","7"],
["8","5","9","7","6","1","4","2","3"],
["4","2","6","8","5","3","7","9","1"],
["7","1","3","9","2","4","8","5","6"],
["9","6","1","5","3","7","2","8","4"],
["2","8","7","4","1","9","6","3","5"],
["3","4","5","2","8","6","1","7","9"]]

*/