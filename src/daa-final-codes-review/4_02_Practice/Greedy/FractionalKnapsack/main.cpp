#include <iostream>
#include "knapsacklist.hpp"
using namespace std;

int main(void) {
    char op;
    int id, value, weight;
    int capacity;

    Knapsack* knapsack = new KnapsackList();
    
    do {
        cout << "Operation: ";
        cin >> op;
        switch (op) {
            case 'i': // insert item
                cin >> id >> value >> weight;
                cout << knapsack->insertItem(id, value, weight) << endl;
                break;
            case 'r': // remove item
                cin >> id;
                cout << knapsack->removeItem(id) << endl;
                break;
            case 'c': // count items
                cout << knapsack->numItems() << endl;
                break;
            case 'f': // fractional knapsack
                cin >> capacity;
                cout << "Max value: " << knapsack->fractionalKnapsack(capacity) << endl;
                break;
            case 'p': // print all items
                knapsack->print();
                break;
            case 'x':
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');

    return 0;
}