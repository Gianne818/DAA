#include <cstdlib>
#include <iostream>
#include "knapsack.hpp"
#include <algorithm>
using namespace std;

class KnapsackList : public Knapsack {
    Item** s_items;
    int num_itm;
    int capacity;

    int getItemIndex(int id) {
        for(int i = 0; i < num_itm; i++) {
            if(s_items[i]->getId() == id) return i;
        }
        return -1;
    }

    public:
    KnapsackList() {
        s_items = (Item**)malloc(100 * sizeof(Item*));
        num_itm = 0;
    }

    int numItems() {
        return num_itm;
    }

    Item** getItems() {
        return s_items;
    }

    bool insertItem(int id, int value, int weight) {
        if(getItemIndex(id) != -1) return false;
        s_items[num_itm++] = new Item(id, value, weight);
        return true;
    }

    bool removeItem(int id) {
        int idx = getItemIndex(id);
        if(idx == -1) return false;
        
        delete s_items[idx];
        for(int j = idx; j < num_itm - 1; j++) {
            s_items[j] = s_items[j + 1];
        }
        num_itm--;
        return true;
    }

    /*
        Fractional Knapsack Greedy Algorithm:
        1. Sort items by value/weight ratio (descending)
        2. Take as much as possible from highest ratio items
        3. If item doesn't fit, take fraction of it
        4. Return total value
    */
    double fractionalKnapsack(int capacity) {
        if(num_itm == 0 || capacity == 0) return 0.0;
        
        // Reset fractions
        for(int i = 0; i < num_itm; i++) {
            s_items[i]->setFraction(1.0);
        }
        
        // Sort by value/weight ratio
        Item** sorted = (Item**)malloc(num_itm * sizeof(Item*));
        for(int i = 0; i < num_itm; i++) {
            sorted[i] = s_items[i];
        }
        
        sort(sorted, sorted + num_itm, itemCompare);
        
        double totalValue = 0.0;
        int remainingCapacity = capacity;
        
        for(int i = 0; i < num_itm && remainingCapacity > 0; i++) {
            if(sorted[i]->getWeight() <= remainingCapacity) {
                // Take whole item
                totalValue += sorted[i]->getValue();
                remainingCapacity -= sorted[i]->getWeight();
                sorted[i]->setFraction(1.0);
            } else {
                // Take fraction of item
                double fraction = (double)remainingCapacity / sorted[i]->getWeight();
                totalValue += sorted[i]->getValue() * fraction;
                sorted[i]->setFraction(fraction);
                remainingCapacity = 0;
            }
        }
        
        free(sorted);
        return totalValue;
    }

    void print() {
        cout << "Items: " << endl;
        for(int i = 0; i < num_itm; i++) {
            s_items[i]->toString();
            cout << endl;
        }
    }
};