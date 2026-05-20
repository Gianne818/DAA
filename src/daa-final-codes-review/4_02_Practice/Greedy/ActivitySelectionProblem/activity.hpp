#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Activity {
    private:
    int id;
    int start;
    int finish;

    public:
    Activity(int i, int s, int f) : id(i), start(s), finish(f) {};

    int getId() { return id; }
    int getStart() { return start; }
    int getFinish() { return finish; }
    
    void setId(int i) { id = i; }
    void setStart(int s) { start = s; }
    void setFinish(int f) { finish = f; }

    void toString() {
        cout << "Activity " << id << ": [" << start << ", " << finish << "]";
    }
};

// Comparator for sorting by finish time
bool activityCompare(Activity* a, Activity* b) {
    return a->getFinish() < b->getFinish();
}
