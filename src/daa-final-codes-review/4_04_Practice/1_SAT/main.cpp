/*
Informal problem: Given a Boolean formula, decide whether there exists an assignment of true/false values to variables that makes the entire formula true.

Natural C++ representation: Use CNF (conjunctive normal form): a vector of clauses , where each clause is a vector of literals , and each literal is a signed integer encoding a variable and its negation).

Backtracking idea: Assign variables one by one (depth-first). At each step, propagate implications and check for any clause that becomes unsatisfied; if so, backtrack immediately. Branch-and-bound can prioritize variables or values that seem more constrained.

Clauses: vector<vector<int>> (each literal as an int with sign)
Assignments: vector<int> or vector<bool> for variable values

SAT	
Boolean formula (CNF)	
Find true/false assignment	
vector<vector<int>> (+/- var)
*/

#include <iostream>
#include "SATSolver.hpp"
using namespace std;

int main() {
    int numVariables;
    int numClauses;

    cout << "===== SAT Solver =====\n\n";
    cout << "Enter number of variables: ";
    cin >> numVariables;

    cout << "Enter number of clauses: ";
    cin >> numClauses;

    vector<vector<int>> clauses;

    cout << "\nInput Clauses\n";
    cout << "Use positive for normal variable\n";
    cout << "Use negative for negation\n\n";

    for (int i = 0; i < numClauses; i++) {
        int literalsCount;

        cout << "Clause " << i + 1 << " literal count: ";
        cin >> literalsCount;

        vector<int> clause;
        cout << "Enter literals:\n";

        for (int j = 0; j < literalsCount; j++) {
            int literal;
            cin >> literal;
            clause.push_back(literal);
        }
        clauses.push_back(clause);
    }

    SATSolver solver(numVariables, clauses);
    solver.run();

    return 0;
}