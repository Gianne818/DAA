#ifndef EXACTCOVER_HPP
#define EXACTCOVER_HPP

#include <iostream>
#include <vector>
#include <set>
#include <cstring>
using namespace std;

class ExactCoverSolver {
private:
    vector<vector<int>> matrix;
    vector<string> rowNames;
    vector<string> colNames;
    vector<int> solution;
    bool found;

private:
    int selectColumn(const vector<bool>& covered) {
        int minCol = -1;
        int minCount = 999999;
        
        for (int j = 0; j < matrix[0].size(); j++) {
            if (!covered[j]) {
                int count = 0;
                for (int i = 0; i < matrix.size(); i++) {
                    if (matrix[i][j] == 1 && !covered[j]) {
                        count++;
                    }
                }
                if (count < minCount) {
                    minCount = count;
                    minCol = j;
                }
            }
        }
        return minCol;
    }

    void coverColumn(int col, vector<bool>& covered, vector<bool>& rowSelected) {
        covered[col] = true;
        
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][col] == 1 && !rowSelected[i]) {
                rowSelected[i] = true;
                for (int j = 0; j < matrix[0].size(); j++) {
                    if (matrix[i][j] == 1) {
                        covered[j] = true;
                    }
                }
            }
        }
    }

    void uncoverColumn(int col, vector<bool>& covered, vector<bool>& rowSelected) {
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][col] == 1 && rowSelected[i]) {
                rowSelected[i] = false;
                for (int j = 0; j < matrix[0].size(); j++) {
                    if (matrix[i][j] == 1) {
                        covered[j] = false;
                    }
                }
            }
        }
        covered[col] = false;
    }

    void backtrack(vector<bool>& covered, vector<bool>& rowSelected) {
        if (found) return;
        
        bool allCovered = true;
        for (int j = 0; j < matrix[0].size(); j++) {
            if (!covered[j]) {
                allCovered = false;
                break;
            }
        }
        
        if (allCovered) {
            found = true;
            return;
        }
        
        int col = selectColumn(covered);
        if (col == -1) return;
        
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][col] == 1 && !rowSelected[i]) {
                solution.push_back(i);
                coverColumn(col, covered, rowSelected);
                backtrack(covered, rowSelected);
                if (found) return;
                solution.pop_back();
                uncoverColumn(col, covered, rowSelected);
            }
        }
    }

public:
    ExactCoverSolver() {
        found = false;
    }

    void setMatrix(const vector<vector<int>>& m, const vector<string>& rows, const vector<string>& cols) {
        matrix = m;
        rowNames = rows;
        colNames = cols;
    }

    void addRow(const vector<int>& row, const string& name) {
        matrix.push_back(row);
        rowNames.push_back(name);
    }

    void setColNames(const vector<string>& cols) {
        colNames = cols;
    }

    bool solve() {
        found = false;
        if (matrix.empty() || matrix[0].empty()) return false;
        
        vector<bool> covered(matrix[0].size(), false);
        vector<bool> rowSelected(matrix.size(), false);
        
        backtrack(covered, rowSelected);
        return found;
    }

    void printMatrix() {
        cout << "\n===== EXACT COVER MATRIX =====" << endl;
        
        cout << "    ";
        for (int j = 0; j < colNames.size(); j++) {
            cout << colNames[j] << " ";
        }
        cout << endl;
        
        for (int i = 0; i < matrix.size(); i++) {
            cout << rowNames[i] << "   ";
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 1) {
                    if (rowNames[i].find('-') != string::npos) {
                        cout << "- ";
                    } else if (rowNames[i].find('|') != string::npos) {
                        cout << "| ";
                    } else {
                        cout << "1 ";
                    }
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    void printSolution() {
        if (!found) {
            cout << "NO - No exact cover exists." << endl;
            return;
        }
        
        cout << "YES - Exact cover found!" << endl;
        cout << "\nSelected rows:" << endl;
        for (int idx : solution) {
            cout << "  " << rowNames[idx];
            
            if (rowNames[idx].find('-') != string::npos) {
                cout << " (horizontal)";
            } else if (rowNames[idx].find('|') != string::npos) {
                cout << " (vertical)";
            }
            cout << endl;
        }
    }
};

#endif