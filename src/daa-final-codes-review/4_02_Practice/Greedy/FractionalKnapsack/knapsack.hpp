#include "fkp.hpp"

class Knapsack {
   public:
    virtual int numItems() = 0;
    virtual Item** getItems() = 0;
    virtual bool insertItem(int id, int value, int weight) = 0;
    virtual bool removeItem(int id) = 0;
    virtual double fractionalKnapsack(int capacity) = 0;
    virtual void print() = 0;
};