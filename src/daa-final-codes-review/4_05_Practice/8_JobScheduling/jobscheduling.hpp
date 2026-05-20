// jobscheduling.hpp

#ifndef JOBSCHEDULING_HPP
#define JOBSCHEDULING_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class JobSchedulingSolver {
private:
    vector<int> jobs;
    int k;
    int x;
    vector<vector<int>> assignment;
    bool found;

private:
    bool isValid(const vector<int>& workloads) {
        for (int load : workloads) {
            if (load > k) return false;
        }
        return true;
    }

    void backtrack(int jobIdx, vector<int>& workloads, vector<vector<int>>& tempAssign) {
        if (found) return;
        
        if (jobIdx == jobs.size()) {
            found = true;
            assignment = tempAssign;
            return;
        }

        for (int worker = 0; worker < x; worker++) {
            if (workloads[worker] + jobs[jobIdx] <= k) {
                workloads[worker] += jobs[jobIdx];
                tempAssign[worker].push_back(jobs[jobIdx]);
                
                backtrack(jobIdx + 1, workloads, tempAssign);
                
                workloads[worker] -= jobs[jobIdx];
                tempAssign[worker].pop_back();
                
                if (found) return;
            }
            
            if (workloads[worker] == 0) break;
        }
    }

public:
    JobSchedulingSolver() {
        k = 0;
        x = 0;
        found = false;
    }

    void setJobs(const vector<int>& jobList) {
        jobs = jobList;
        sort(jobs.begin(), jobs.end(), greater<int>());
    }

    bool solve(int deadline, int workers) {
        k = deadline;
        x = workers;
        found = false;
        
        if (jobs.empty()) return true;
        
        int total = accumulate(jobs.begin(), jobs.end(), 0);
        if (total > k * x) return false;
        if (jobs[0] > k) return false;
        
        vector<int> workloads(x, 0);
        vector<vector<int>> tempAssign(x);
        
        backtrack(0, workloads, tempAssign);
        return found;
    }

    void printSchedule() {
        if (!found) {
            cout << "No valid schedule exists with " << x 
                 << " workers and " << k << " hours deadline per worker." << endl;
            return;
        }

        cout << "\n===== JOB SCHEDULE =====" << endl;
        for (int i = 0; i < assignment.size(); i++) {
            cout << "Worker " << i + 1 << ": ";
            if (assignment[i].empty()) {
                cout << "(no jobs)";
            } else {
                int total = 0;
                for (int j = 0; j < assignment[i].size(); j++) {
                    cout << assignment[i][j];
                    total += assignment[i][j];
                    if (j < assignment[i].size() - 1) cout << ", ";
                }
                cout << " | Total: " << total << " hours";
            }
            cout << endl;
        }
    }
};

#endif