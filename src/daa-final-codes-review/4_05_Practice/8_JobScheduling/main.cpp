/*
Inputs: List of integers(hours)
    k deadline per worker(hours)
    x workers
Output: List of List of integers 
    Worker 1:
    Worker ...:
    Worker x:
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "jobscheduling.hpp"

using namespace std;

int main() {
    vector<int> jobs;
    int k, x;
    string input;
    
    JobSchedulingSolver scheduler;
    
    cout << "===== JOB SCHEDULING SOLVER =====" << endl;
    cout << "Problem: Assign jobs to workers with deadline per worker." << endl;
    cout << endl;
    
    cout << "Enter job list (space-separated integers): ";
    getline(cin, input);
    
    stringstream ss(input);
    int num;
    while (ss >> num) {
        jobs.push_back(num);
    }
    
    sort(jobs.begin(), jobs.end(), greater<int>());
    scheduler.setJobs(jobs);
    
    cout << "Jobs: { ";
    for (int i = 0; i < jobs.size(); i++) {
        cout << jobs[i];
        if (i < jobs.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
    cout << endl;
    
    cout << "Enter deadline per worker (k): ";
    cin >> k;
    
    cout << "Enter number of workers (x): ";
    cin >> x;
    
    cout << endl;
    cout << "Scheduling with " << x << " workers, "
         << k << " hours deadline per worker..." << endl;
    
    if (scheduler.solve(k, x)) {
        cout << "Schedule found!" << endl;
        scheduler.printSchedule();
    } else {
        cout << "No valid schedule exists." << endl;
    }
    
    return 0;
}
/*
===== JOB SCHEDULING SOLVER =====
Problem: Assign jobs to workers with deadline per worker.

Enter job list (space-separated integers): 2 3 5 4 4 6
Jobs: { 6, 5, 4, 4, 3, 2 }

Enter deadline per worker (k): 8
Enter number of workers (x): 3

Scheduling with 3 workers, 8 hours deadline per worker...
Schedule found!

===== JOB SCHEDULE =====
Worker 1: 6, 2 | Total: 8 hours
Worker 2: 5, 3 | Total: 8 hours
Worker 3: 4, 4 | Total: 8 hours
*/

/*
===== JOB SCHEDULING SOLVER =====
Problem: Assign jobs to workers with deadline per worker.

Enter job list (space-separated integers): 1 2 3 5 6
Jobs: { 6, 5, 3, 2, 1 }

Enter deadline per worker (k): 4
Enter number of workers (x): 4

Scheduling with 4 workers, 4 hours deadline per worker...
No valid schedule exists.
*/