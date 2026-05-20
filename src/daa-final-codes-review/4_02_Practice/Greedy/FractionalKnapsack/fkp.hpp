
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Item {
    private:
    int id;
    int value;
    int weight;
    double fraction; // for fractional selection

    public:
    Item(int i, int v, int w) : id(i), value(v), weight(w), fraction(1.0) {};

    int getId() { return id; }
    int getValue() { return value; }
    int getWeight() { return weight; }
    double getFraction() { return fraction; }
    
    void setFraction(double f) { fraction = f; }
    void setId(int i) { id = i; }
    void setValue(int v) { value = v; }
    void setWeight(int w) { weight = w; }

    double getValuePerWeight() {
        return (double)value / weight;
    }

    void toString() {
        cout << "Item " << id << ": value=" << value 
             << ", weight=" << weight 
             << ", fraction=" << fraction;
    }
};

// Comparator for sorting by value/weight ratio (descending)
bool itemCompare(Item* a, Item* b) {
    return a->getValuePerWeight() > b->getValuePerWeight();
}