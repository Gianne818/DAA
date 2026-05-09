#include <iostream>
using namespace std;


bool checkValidity(int board[9][9], int row, int col, int num){
    
    //check if number is already in col
    for(int i = 0; i<9; i++){
        if(board[row][i] == num) return false;
    }
    
    //check if number is already in row
    for(int i = 0; i<9; i++){
        if(board[i][col] == num) return false;
    }
    
    int rowStart = row - (row%3);
    int colStart = col - (col%3);
    
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(board[rowStart+i][colStart+j] == num) return false;
        }
    }
    return true;
}


bool solveCurrent(int board[9][9], int row, int col){
    int s = 9;
    
    // base case: last row last col, solved
    if(row == s-1 && col == s) return true;
    
    //if reached end column
    if(col == s){
        row++;
        col = 0;
    }
    
    // if current cell is already solved
    if(board[row][col] != 0){
        return solveCurrent(board, row, col+1);
    }
    
    
    for(int i = 1; i<=9; i++){
        if(checkValidity(board, row, col, i)){
            board[row][col] = i;
            if(solveCurrent(board, row, col+1)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}


void solve (int board[9][9]){
    solveCurrent(board, 0, 0);
}


void printBoard(int board[9][9]){
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main (){
    cout << "Enter the Sudoku board:\n";
    
    int board[9][9];
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            cin >>  board[i][j];
        }
    }
    
    cout << "\nSolved Board:\n";
    solve(board);
    
    printBoard(board);
}