#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
    SAT Solver using Backtracking (DFS)

    CNF Format Example:
    (x1 OR !x2) AND (!x1 OR x3)

    Input:
    Number of variables
    Number of clauses

    Each clause:
    Number of literals
    Literals

    Literal Encoding:
    Positive  -> normal variable
    Negative  -> negated variable

    Example:
    x1      -> 1
    !x1     -> -1
    x2      -> 2
    !x2     -> -2
*/

class SATSolver {
private:
    int numVariables;
    vector<vector<int>> clauses;

    // -1 = unassigned
    //  0 = false
    //  1 = true
    vector<int> assignment;

public:

    SATSolver(int vars, vector<vector<int>> c) {
        numVariables = vars;
        clauses = c;
        assignment.resize(numVariables + 1, -1);
    }

    // Check if a literal is TRUE
    bool isLiteralTrue(int literal) {
        int var = abs(literal);

        if (assignment[var] == -1) return false;

        // Positive literal
        if (literal > 0) return assignment[var] == 1;

        // Negative literal
        return assignment[var] == 0;
    }

    // Check if a literal is FALSE
    bool isLiteralFalse(int literal) {
        int var = abs(literal);
        if (assignment[var] == -1) return false;

        // Positive literal
        if (literal > 0) return assignment[var] == 0;

        // Negative literal
        return assignment[var] == 1;
    }

    // Check if a clause is satisfied
    bool isClauseSatisfied(vector<int>& clause) {
        for (int literal : clause) {
            if (isLiteralTrue(literal)) return true;
        }
        return false;
    }

    // Check if clause became impossible
    bool isClauseUnsatisfied(vector<int>& clause) {
        for (int literal : clause) {
            // Clause still possible
            if (!isLiteralFalse(literal)) return false;
        }
        // All literals false
        return true;
    }

    // Early pruning
    bool hasConflict() {
        for (auto& clause : clauses) {
            if (isClauseUnsatisfied(clause)) return true;
        }
        return false;
    }

    // Check if all clauses satisfied
    bool allClausesSatisfied() {
        for (auto& clause : clauses) {
            if (!isClauseSatisfied(clause)) return false;
        }
        return true;
    }

    // Backtracking DFS
    bool solve(int variable) {
        // Base Case
        if (variable > numVariables) {
            return allClausesSatisfied();
        }
        // Try TRUE
        assignment[variable] = 1;
        if (!hasConflict()) {
            if (solve(variable + 1)) return true;
        }
        // Try FALSE
        assignment[variable] = 0;
        if (!hasConflict()) {
            if (solve(variable + 1)) return true;
        }
        // Backtrack
        assignment[variable] = -1;
        return false;
    }

    void printSolution() {
        cout << "\nSATISFIABLE\n";
        cout << "Variable Assignments:\n";
        for (int i = 1; i <= numVariables; i++) {
            cout << "x" << i << " = ";
            if (assignment[i] == 1) cout << "TRUE";
            else cout << "FALSE";
            cout << "\n";
        }
    }

    void run() {
        bool possible = solve(1);
        if (possible) printSolution();
        else cout << "\nUNSATISFIABLE\n";
    }
};