/*

Use adjacency Matrix, use '-' for horizontal AND '|' if vertical.

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "exactcover.hpp"

using namespace std;

int main() {
    ExactCoverSolver solver;
    
    cout << "===== EXACT COVER SOLVER =====" << endl;
    cout << "Problem: Select rows such that each column is covered exactly once." << endl;
    cout << "Use '-' for horizontal placements, '|' for vertical placements." << endl;
    cout << endl;
    
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    
    vector<string> rowNames(rows);
    vector<string> colNames(cols);
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));
    
    cout << "\nEnter column names (" << cols << "): ";
    for (int j = 0; j < cols; j++) {
        cin >> colNames[j];
    }
    
    cout << "\nEnter rows with format: name [column_indices]" << endl;
    cout << "Example: 'A-1 0 2 3' means row 'A-1' covers columns 0,2,3" << endl;
    cout << "Use '-' for horizontal, '|' for vertical in row name" << endl;
    cout << endl;
    
    cin.ignore();
    for (int i = 0; i < rows; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        
        ss >> rowNames[i];
        
        int colIdx;
        while (ss >> colIdx) {
            if (colIdx >= 0 && colIdx < cols) {
                matrix[i][colIdx] = 1;
            }
        }
    }
    
    solver.setMatrix(matrix, rowNames, colNames);
    
    cout << "\nInput matrix:" << endl;
    solver.printMatrix();
    
    cout << "\nSolving exact cover..." << endl;
    
    if (solver.solve()) {
        solver.printSolution();
    } else {
        solver.printSolution();
    }
    
    return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 1 - Simple Exact Cover (Pentomino Placement)
===== EXACT COVER SOLVER =====
Enter number of rows: 6
Enter number of columns: 4

Enter column names (4): 1 2 3 4

Enter rows with format: name [column_indices]
Example: 'A-1 0 2 3' means row 'A-1' covers columns 0,2,3
Use '-' for horizontal, '|' for vertical in row name

A-1 0 1
A-2 0 2
B-1 1 2
B-2 1 3
C-1 2 3
C-2 0 3

Input matrix:
===== EXACT COVER MATRIX ====
    1 2 3 4 
A-1   - - 0 0 
A-2   - 0 - 0 
B-1   0 - - 0 
B-2   0 - 0 - 
C-1   0 0 - - 
C-2   - 0 0 - 

Solving exact cover...
YES - Exact cover found!

Selected rows:
  A-1 (horizontal)
  B-2 (vertical)
  C-1 (horizontal)

Notes:
    - Proves that that whole 6 x 4 matrix can be all fitted. 
    - Rows A-1, B-2, C-1 cover each column (1,2,3,4) exactly once.
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 2 - 2x2 Tiling Problem
===== EXACT COVER SOLVER ====
Problem: Select rows such that each column is covered exactly once.

Enter number of rows: 4
Enter number of columns: 4

Enter column names (4): A B C D

Enter rows with format: name [column_indices]
Use '-' for horizontal, '|' for vertical in row name

H1-0 1
H2-2 3
V1-0 2
V2-1 3

Input matrix:
===== EXACT COVER MATRIX ====
    A B C D 
H1-0   - - 0 0 
H2-2   0 0 - - 
V1-0   - 0 - 0 
V2-1   0 - 0 - 

Solving exact cover...
YES - Exact cover found!

Selected rows:
  H1-0 (horizontal)
  H2-2 (horizontal)
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 3 - No Solution (Overlapping Constraints)
===== EXACT COVER SOLVER ====
Problem: Select rows such that each column is covered exactly once.

Enter number of rows: 3
Enter number of columns: 3

Enter column names (3): X Y Z

Enter rows with format: name [column_indices]
Use '-' for horizontal, '|' for vertical in row name

Row1-0 1
Row2-1 2
Row3-0 2

Input matrix:
===== EXACT COVER MATRIX ====
    X Y Z 
Row1-0   - - 0 
Row2-1   0 - - 
Row3-0   - 0 - 

Solving exact cover...
NO - No exact cover exists.
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 4 - Exact Cover for 3x3 Grid with Tetrominoes
===== EXACT COVER SOLVER ====
Enter number of rows: 5
Enter number of columns: 9

Enter column names (9): A1 A2 A3 B1 B2 B3 C1 C2 C3

Enter rows with format: name [column_indices]

L-1 0 1 3
L-2 1 2 5
L-3 3 4 6
L-4 4 5 7
L-5 6 7 8

Input matrix:
===== EXACT COVER MATRIX ====
    A1 A2 A3 B1 B2 B3 C1 C2 C3 
L-1   - - 0 - 0 0 0 0 0 
L-2   0 - - 0 0 - 0 0 0 
L-3   0 0 0 - - 0 - 0 0 
L-4   0 0 0 0 - - 0 - 0 
L-5   0 0 0 0 0 0 - - - 

Solving exact cover...
YES - Exact cover found!

Selected rows:
  L-1 (horizontal)
  L-2 (horizontal)
  L-3 (horizontal)
  L-4 (horizontal)
  L-5 (horizontal)
*/