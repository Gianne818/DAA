#include "activity.hpp"

class ActivitySelector {
   public:
    virtual int numActivities() = 0;
    virtual Activity** getActivities() = 0;
    virtual bool insertActivity(int id, int start, int finish) = 0;
    virtual bool removeActivity(int id) = 0;
    virtual Activity** greedyActivitySelector() = 0;
    virtual void print() = 0;
};