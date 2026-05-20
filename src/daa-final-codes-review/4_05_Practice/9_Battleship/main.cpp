/*

Input:
• An N × N grid with certain squares pre-filled (e.g., water, ship segments).
• Row constraints: An array of numbers indicating how many ship segments
are in each row.
• Column constraints: An array of numbers indicating how many ship
segments are in each column.
• A fleet list: The quantity and sizes of ships that must be placed 
(e.g., one 1 × 4, two 1 × 3).

Is there a valid configuration of the remaining ships on the grid that satisfies all row/column segment counts without any two ships touching (even diagonally)?

Output:
- YES (if a valid placement exists).
- NO (if no placement can satisfy the criteria).



*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "battleship.hpp"

using namespace std;

int main() {
    BattleshipSolver solver;
    int N;
    vector<vector<char>> grid;
    vector<int> rowConstraints;
    vector<int> colConstraints;
    vector<pair<int, int>> fleet;
    
    cout << "===== BATTLESHIP SOLVER =====" << endl;
    cout << "Problem: Place ships on N×N grid satisfying row/column counts" << endl;
    cout << "and fleet requirements. Ships cannot touch (even diagonally)." << endl;
    cout << endl;
    
    cout << "Enter grid size N: ";
    cin >> N;
    
    cout << "\nEnter initial grid (" << N << " rows):" << endl;
    cout << "Use '.' for water, 'S' for pre-placed ship segment" << endl;
    grid.resize(N, vector<char>(N));
    
    for (int i = 0; i < N; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < N; j++) {
            grid[i][j] = row[j];
        }
    }
    
    cout << "\nEnter row constraints (" << N << " numbers): ";
    rowConstraints.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> rowConstraints[i];
    }
    
    cout << "Enter column constraints (" << N << " numbers): ";
    colConstraints.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> colConstraints[i];
    }
    
    cout << "\nEnter fleet (size and quantity, end with 0 0):" << endl;
    cout << "Example: 4 1  (one size-4 ship)" << endl;
    cout << "         3 2  (two size-3 ships)" << endl;
    cout << "         0 0  (to finish)" << endl;
    
    int size, quantity;
    while (true) {
        cin >> size >> quantity;
        if (size == 0 && quantity == 0) break;
        fleet.push_back({size, quantity});
    }
    
    solver.setGrid(N, grid);
    solver.setRowConstraints(rowConstraints);
    solver.setColConstraints(colConstraints);
    solver.setFleet(fleet);
    
    cout << "\nSolving..." << endl;
    
    if (solver.solve()) {
        solver.printResult();
    } else {
        solver.printResult();
    }
    
    return 0;
}

/* TC 1 - Simple 4x4 Grid
===== BATTLESHIP SOLVER =====
Enter grid size N: 4

Enter initial grid (4 rows):
Use '.' for water, 'S' for pre-placed ship segment
....
....
....
....

Enter row constraints (4 numbers): 2 2 2 2
Enter column constraints (4 numbers): 2 2 2 2

Enter fleet (size and quantity, end with 0 0):
Example: 4 1  (one size-4 ship)
         3 2  (two size-3 ships)
         0 0  (to finish)
2 4
0 0

Solving...
YES - Valid configuration exists!

===== BATTLESHIP GRID =====
   0 1 2 3
0  S S . .  | 2
1  S S . .  | 2
2  . . S S  | 2
3  . . S S  | 2
   - - - -
   2 2 2 2
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 2 - Unsolvable (Too Many Ships)
Enter grid size N: 3

Enter initial grid (3 rows):
...
...
...

Enter row constraints (3 numbers): 1 1 1
Enter column constraints (3 numbers): 1 1 1

Enter fleet (size and quantity, end with 0 0):
2 2
0 0

Solving...
NO - No valid placement satisfies all criteria.
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 3 - With Pre-placed Ships
Enter grid size N: 5

Enter initial grid (5 rows):
.....
.S...
.....
...S.
.....

Enter row constraints (5 numbers): 2 2 1 2 1
Enter column constraints (5 numbers): 1 2 1 2 1

Enter fleet (size and quantity, end with 0 0):
3 1
2 2
0 0

Solving...
YES - Valid configuration exists!
*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* TC 4 - Battleship (One 4-length ship)
Enter grid size N: 4

Enter initial grid (4 rows):
....
....
....
....

Enter row constraints (4 numbers): 1 1 1 1
Enter column constraints (4 numbers): 1 1 1 1

Enter fleet (size and quantity, end with 0 0):
4 1
0 0

Solving...
YES - Valid configuration exists!

===== BATTLESHIP GRID =====
   0 1 2 3
0  S . . .  | 1
1  S . . .  | 1
2  S . . .  | 1
3  S . . .  | 1
   - - - -
   4 0 0 0
*/