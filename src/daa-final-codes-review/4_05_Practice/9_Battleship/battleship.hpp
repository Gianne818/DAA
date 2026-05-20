#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class BattleshipSolver {
private:
    int N;
    vector<vector<char>> grid;
    vector<int> rowConstraints;
    vector<int> colConstraints;
    vector<pair<int, int>> fleet;
    bool found;

private:
    bool isValidPlacement(int row, int col, int size, bool horizontal) {
        if (horizontal) {
            if (col + size > N) return false;
            for (int i = 0; i < size; i++) {
                if (grid[row][col + i] != '.') return false;
            }
            for (int i = -1; i <= size; i++) {
                for (int j = -1; j <= 1; j++) {
                    int r = row + j;
                    int c = col + i;
                    if (r >= 0 && r < N && c >= 0 && c < N) {
                        if (grid[r][c] == 'S') return false;
                    }
                }
            }
            if (row - 1 >= 0) {
                for (int i = 0; i < size; i++) {
                    if (grid[row - 1][col + i] == 'S') return false;
                }
            }
            if (row + 1 < N) {
                for (int i = 0; i < size; i++) {
                    if (grid[row + 1][col + i] == 'S') return false;
                }
            }
        } else {
            if (row + size > N) return false;
            for (int i = 0; i < size; i++) {
                if (grid[row + i][col] != '.') return false;
            }
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= size; j++) {
                    int r = row + j;
                    int c = col + i;
                    if (r >= 0 && r < N && c >= 0 && c < N) {
                        if (grid[r][c] == 'S') return false;
                    }
                }
            }
            if (col - 1 >= 0) {
                for (int i = 0; i < size; i++) {
                    if (grid[row + i][col - 1] == 'S') return false;
                }
            }
            if (col + 1 < N) {
                for (int i = 0; i < size; i++) {
                    if (grid[row + i][col + 1] == 'S') return false;
                }
            }
        }
        return true;
    }

    void placeShip(int row, int col, int size, bool horizontal, char mark) {
        if (horizontal) {
            for (int i = 0; i < size; i++) {
                grid[row][col + i] = mark;
            }
        } else {
            for (int i = 0; i < size; i++) {
                grid[row + i][col] = mark;
            }
        }
    }

    bool checkConstraints() {
        vector<int> rowCount(N, 0);
        vector<int> colCount(N, 0);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 'S') {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }
        
        for (int i = 0; i < N; i++) {
            if (rowCount[i] > rowConstraints[i]) return false;
            if (colCount[i] > colConstraints[i]) return false;
        }
        return true;
    }

    bool checkFinalConstraints() {
        vector<int> rowCount(N, 0);
        vector<int> colCount(N, 0);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 'S') {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }
        
        for (int i = 0; i < N; i++) {
            if (rowCount[i] != rowConstraints[i]) return false;
            if (colCount[i] != colConstraints[i]) return false;
        }
        return true;
    }

    void backtrack(int shipIdx) {
        if (found) return;
        
        if (shipIdx == fleet.size()) {
            if (checkFinalConstraints()) {
                found = true;
            }
            return;
        }
        
        int size = fleet[shipIdx].first;
        int count = fleet[shipIdx].second;
        
        for (int c = 0; c < count; c++) {
            bool placed = false;
            
            for (int i = 0; i < N && !placed; i++) {
                for (int j = 0; j < N && !placed; j++) {
                    if (isValidPlacement(i, j, size, true)) {
                        placeShip(i, j, size, true, 'S');
                        if (checkConstraints()) {
                            backtrack(shipIdx + 1);
                            if (found) return;
                        }
                        placeShip(i, j, size, true, '.');
                    }
                    
                    if (isValidPlacement(i, j, size, false)) {
                        placeShip(i, j, size, false, 'S');
                        if (checkConstraints()) {
                            backtrack(shipIdx + 1);
                            if (found) return;
                        }
                        placeShip(i, j, size, false, '.');
                    }
                }
            }
            
            if (!placed) return;
        }
    }

public:
    BattleshipSolver() {
        N = 0;
        found = false;
    }

    void setGrid(int n, const vector<vector<char>>& initialGrid) {
        N = n;
        grid = initialGrid;
    }

    void setRowConstraints(const vector<int>& rows) {
        rowConstraints = rows;
    }

    void setColConstraints(const vector<int>& cols) {
        colConstraints = cols;
    }

    void setFleet(const vector<pair<int, int>>& fleetList) {
        fleet = fleetList;
    }

    bool solve() {
        found = false;
        if (!checkConstraints()) return false;
        backtrack(0);
        return found;
    }

    void printGrid() {
        cout << "\n===== BATTLESHIP GRID =====" << endl;
        cout << "   ";
        for (int j = 0; j < N; j++) {
            cout << j << " ";
        }
        cout << endl;
        
        for (int i = 0; i < N; i++) {
            cout << i << "  ";
            for (int j = 0; j < N; j++) {
                cout << grid[i][j] << " ";
            }
            cout << " | " << rowConstraints[i] << endl;
        }
        
        cout << "   ";
        for (int j = 0; j < N; j++) {
            cout << "--";
        }
        cout << endl;
        cout << "   ";
        for (int j = 0; j < N; j++) {
            cout << colConstraints[j] << " ";
        }
        cout << endl;
    }

    void printResult() {
        if (found) {
            cout << "YES - Valid configuration exists!" << endl;
            printGrid();
        } else {
            cout << "NO - No valid placement satisfies all criteria." << endl;
        }
    }
};

#endif