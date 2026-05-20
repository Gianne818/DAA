#include <cstdlib>
#include <iostream>
#include "activities.hpp"
#include <algorithm>
using namespace std;

class ActivityList : public ActivitySelector {
    Activity** s_activities;
    int num_act;
    int capacity;

    int getActivityIndex(int id) {
        for(int i = 0; i < num_act; i++) {
            if(s_activities[i]->getId() == id) return i;
        }
        return -1;
    }

    public:
    ActivityList() {
        capacity = 100;
        s_activities = (Activity**)malloc(capacity * sizeof(Activity*));
        num_act = 0;
    }

    int numActivities() {
        return num_act;
    }

    Activity** getActivities() {
        return s_activities;
    }

    bool insertActivity(int id, int start, int finish) {
        if(getActivityIndex(id) != -1) return false;
        if(num_act >= capacity) return false;
        
        s_activities[num_act++] = new Activity(id, start, finish);
        return true;
    }

    bool removeActivity(int id) {
        int idx = getActivityIndex(id);
        if(idx == -1) return false;
        
        delete s_activities[idx];
        for(int j = idx; j < num_act - 1; j++) {
            s_activities[j] = s_activities[j + 1];
        }
        num_act--;
        return true;
    }

    /*
        Greedy Activity Selection Algorithm:
        1. Sort activities by finish time (already sorted in input)
        2. Select first activity
        3. For each subsequent activity, if start >= last finish, select it
    */
    Activity** greedyActivitySelector() {
        if(num_act == 0) return nullptr;
        
        // Sort by finish time
        Activity** sorted = (Activity**)malloc(num_act * sizeof(Activity*));
        for(int i = 0; i < num_act; i++) {
            sorted[i] = s_activities[i];
        }
        
        sort(sorted, sorted + num_act, activityCompare);
        
        // Select activities
        Activity** selected = (Activity**)malloc(num_act * sizeof(Activity*));
        int selectedCount = 0;
        
        selected[selectedCount++] = sorted[0];
        int lastFinish = sorted[0]->getFinish();
        
        for(int i = 1; i < num_act; i++) {
            if(sorted[i]->getStart() >= lastFinish) {
                selected[selectedCount++] = sorted[i];
                lastFinish = sorted[i]->getFinish();
            }
        }
        
        // Trim to exact size
        Activity** result = (Activity**)malloc(selectedCount * sizeof(Activity*));
        for(int i = 0; i < selectedCount; i++) {
            result[i] = selected[i];
        }
        free(selected);
        free(sorted);
        return result;
    }

    void print() {
        cout << "Activities: " << endl;
        for(int i = 0; i < num_act; i++) {
            s_activities[i]->toString();
            cout << endl;
        }
    }
};